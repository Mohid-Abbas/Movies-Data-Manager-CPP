#pragma once
#include "AVLTree.h"
#include "HashTable.h"
#include "MovieNode.h"
#include "ActorNode.h"
#include "GenreNode.h"
#include "DirectorNode.h"
#include "Graph.h"
#include "CSVParser.h"
#include "LinkedList.h"
#include <iostream>

// DataManager - Central class for managing all movie data
class DataManager {
private:
    AVLTree<MovieNode> movieTree;                    // Movies indexed by title
    HashTable<String, ActorNode*> actorTable;        // Actors hash table
    HashTable<String, GenreNode*> genreTable;        // Genres hash table
    HashTable<String, DirectorNode*> directorTable;  // Directors hash table
    MovieGraph graph;                                 // Movie relationship graph
    
    LinkedList<MovieNode*> allMovies;  // Keep pointers to all movies for graph
    int totalMoviesLoaded;

    // Helper: Get or create actor
    ActorNode* getOrCreateActor(const String& actorName) {
        if (actorName.isEmpty()) return nullptr;

        ActorNode** existingActor = actorTable.search(actorName);
        if (existingActor != nullptr) {
            return *existingActor;
        }

        ActorNode* newActor = new ActorNode(actorName);
        actorTable.insert(actorName, newActor);
        return newActor;
    }

    // Helper: Get or create genre
    GenreNode* getOrCreateGenre(const String& genreName) {
        if (genreName.isEmpty()) return nullptr;

        GenreNode** existingGenre = genreTable.search(genreName);
        if (existingGenre != nullptr) {
            return *existingGenre;
        }

        GenreNode* newGenre = new GenreNode(genreName);
        genreTable.insert(genreName, newGenre);
        return newGenre;
    }

    // Helper: Get or create director
    DirectorNode* getOrCreateDirector(const String& directorName) {
        if (directorName.isEmpty()) return nullptr;

        DirectorNode** existingDirector = directorTable.search(directorName);
        if (existingDirector != nullptr) {
            return *existingDirector;
        }

        DirectorNode* newDirector = new DirectorNode(directorName);
        directorTable.insert(directorName, newDirector);
        return newDirector;
    }

public:
    // Constructor
    DataManager() : totalMoviesLoaded(0) {}

    // Destructor
    ~DataManager() {
        // Clean up actors
        LinkedList<ActorNode*> actors = actorTable.getValues();
        for (auto it = actors.begin(); it != actors.end(); ++it) {
            delete *it;
        }

        // Clean up genres
        LinkedList<GenreNode*> genres = genreTable.getValues();
        for (auto it = genres.begin(); it != genres.end(); ++it) {
            delete *it;
        }

        // Clean up directors
        LinkedList<DirectorNode*> directors = directorTable.getValues();
        for (auto it = directors.begin(); it != directors.end(); ++it) {
            delete *it;
        }

        // Clean up movie pointers list
        for (auto it = allMovies.begin(); it != allMovies.end(); ++it) {
            // Note: Movies themselves are managed by AVL tree
            // We're just clearing the pointer list
        }
    }

    // Load dataset from CSV file
    bool loadFromCSV(const char* filename) {
        std::cout << "Loading dataset from " << filename << "..." << std::endl;

        LinkedList<LinkedList<String>> data = CSVParser::readCSV(filename);
        
        if (data.isEmpty()) {
            std::cout << "Error: No data loaded from file." << std::endl;
            return false;
        }

        std::cout << "Parsing " << data.getSize() << " movies..." << std::endl;

        // CSV columns (based on provided sample):
        // 0:color, 1:director_name, 2:num_critic_for_reviews, 3:duration,
        // 4:director_facebook_likes, 5:actor_3_facebook_likes, 6:actor_2_name,
        // 7:actor_1_facebook_likes, 8:gross, 9:genres, 10:actor_1_name,
        // 11:movie_title, 12:num_voted_users, 13:cast_total_facebook_likes,
        // 14:actor_3_name, 15:facenumber_in_poster, 16:plot_keywords,
        // 17:movie_imdb_link, 18:num_user_for_reviews, 19:language,
        // 20:country, 21:content_rating, 22:budget, 23:title_year,
        // 24:actor_2_facebook_likes, 25:imdb_score, 26:aspect_ratio,
        // 27:movie_facebook_likes

        for (auto it = data.begin(); it != data.end(); ++it) {
            LinkedList<String>& fields = *it;
            
            if (fields.getSize() < 28) continue;  // Skip incomplete rows

            // Create movie node
            MovieNode movie;
            
            // Set basic info (clean non-ASCII characters from title)
            movie.setTitle(fields.get(11).trim().removeNonASCII());
            movie.setDirector(fields.get(1).trim().removeNonASCII());
            movie.setYear(CSVParser::toInt(fields.get(23)));
            movie.setImdbScore(CSVParser::toDouble(fields.get(25)));
            movie.setDuration(CSVParser::toInt(fields.get(3)));
            movie.setBudget(CSVParser::toLongLong(fields.get(22)));
            movie.setGross(CSVParser::toLongLong(fields.get(8)));
            movie.setContentRating(fields.get(21).trim());
            movie.setLanguage(fields.get(19).trim());
            movie.setCountry(fields.get(20).trim());
            movie.setColor(fields.get(0).trim());
            movie.setNumVotedUsers(CSVParser::toInt(fields.get(12)));
            movie.setNumCriticReviews(CSVParser::toInt(fields.get(2)));
            movie.setNumUserReviews(CSVParser::toInt(fields.get(18)));
            movie.setAspectRatio(CSVParser::toDouble(fields.get(26)));
            movie.setMovieFacebookLikes(CSVParser::toInt(fields.get(27)));

            // Parse and add genres (pipe-separated)
            String genresStr = fields.get(9).trim();
            LinkedList<String> genres = CSVParser::splitString(genresStr, '|');
            for (auto genreIt = genres.begin(); genreIt != genres.end(); ++genreIt) {
                movie.addGenre(*genreIt);
            }

            // Parse and add plot keywords (pipe-separated)
            String keywordsStr = fields.get(16).trim();
            LinkedList<String> keywords = CSVParser::splitString(keywordsStr, '|');
            for (auto kwIt = keywords.begin(); kwIt != keywords.end(); ++kwIt) {
                movie.addPlotKeyword(*kwIt);
            }

            // Add actors (clean non-ASCII characters)
            String actor1 = fields.get(10).trim().removeNonASCII();
            String actor2 = fields.get(6).trim().removeNonASCII();
            String actor3 = fields.get(14).trim().removeNonASCII();
            
            if (!actor1.isEmpty()) movie.addActor(actor1);
            if (!actor2.isEmpty()) movie.addActor(actor2);
            if (!actor3.isEmpty()) movie.addActor(actor3);

            // Insert movie into AVL tree
            movieTree.insert(movie);
            totalMoviesLoaded++;

            // Get pointer to the movie in the tree
            MovieNode* moviePtr = movieTree.find(movie);
            if (moviePtr != nullptr) {
                allMovies.append(moviePtr);

                // Update actor filmographies
                if (!actor1.isEmpty()) {
                    ActorNode* actorNode = getOrCreateActor(actor1);
                    if (actorNode != nullptr) {
                        actorNode->addMovie(moviePtr);
                    }
                }
                if (!actor2.isEmpty()) {
                    ActorNode* actorNode = getOrCreateActor(actor2);
                    if (actorNode != nullptr) {
                        actorNode->addMovie(moviePtr);
                    }
                }
                if (!actor3.isEmpty()) {
                    ActorNode* actorNode = getOrCreateActor(actor3);
                    if (actorNode != nullptr) {
                        actorNode->addMovie(moviePtr);
                    }
                }

                // Update genre collections
                for (auto genreIt = genres.begin(); genreIt != genres.end(); ++genreIt) {
                    GenreNode* genreNode = getOrCreateGenre(*genreIt);
                    if (genreNode != nullptr) {
                        genreNode->addMovie(moviePtr);
                    }
                }

                // Update director filmography
                if (!movie.getDirector().isEmpty()) {
                    DirectorNode* directorNode = getOrCreateDirector(movie.getDirector());
                    if (directorNode != nullptr) {
                        directorNode->addMovie(moviePtr);
                    }
                }
            }
        }

        std::cout << "Successfully loaded " << totalMoviesLoaded << " movies." << std::endl;
        std::cout << "Total actors: " << actorTable.getSize() << std::endl;
        std::cout << "Total genres: " << genreTable.getSize() << std::endl;
        std::cout << "Total directors: " << directorTable.getSize() << std::endl;

        return true;
    }

    // Build movie relationship graph
    void buildGraph() {
        std::cout << "\nBuilding movie relationship graph..." << std::endl;
        
        // Add all movies to graph
        for (auto it = allMovies.begin(); it != allMovies.end(); ++it) {
            graph.addMovie(*it);
        }

        // Build edges
        graph.buildEdges();
        
        std::cout << "Graph built successfully!" << std::endl;
        graph.displayStatistics();
    }

    // Search movie by exact title
    MovieNode* searchMovieByTitle(const String& title) {
        MovieNode searchKey(title);
        return movieTree.find(searchKey);
    }

    // Search movie by title (flexible - case insensitive and partial match)
    MovieNode* searchMovieByTitleFlexible(const String& title) {
        String searchLower = title.toLower();
        
        // First try exact match
        MovieNode* exact = searchMovieByTitle(title);
        if (exact != nullptr) return exact;
        
        // Try case-insensitive search
        for (auto it = allMovies.begin(); it != allMovies.end(); ++it) {
            MovieNode* movie = *it;
            String movieTitleLower = movie->getTitle().toLower();
            
            // Exact match (case insensitive)
            if (movieTitleLower == searchLower) {
                return movie;
            }
        }
        
        // Try partial match (contains)
        for (auto it = allMovies.begin(); it != allMovies.end(); ++it) {
            MovieNode* movie = *it;
            String movieTitleLower = movie->getTitle().toLower();
            
            if (movieTitleLower.find(searchLower) != -1) {
                return movie;
            }
        }
        
        return nullptr;
    }

    // Get all movie titles (for debugging)
    LinkedList<String> getAllMovieTitles() {
        LinkedList<String> titles;
        for (auto it = allMovies.begin(); it != allMovies.end(); ++it) {
            titles.append((*it)->getTitle());
        }
        return titles;
    }

    // Search movies by actor (exact match)
    LinkedList<MovieNode*> searchMoviesByActor(const String& actorName) {
        LinkedList<MovieNode*> results;
        
        ActorNode** actorPtr = actorTable.search(actorName);
        if (actorPtr != nullptr) {
            return (*actorPtr)->getMovies();
        }
        
        return results;
    }

    // Search movies by actor (flexible - case insensitive and partial)
    LinkedList<MovieNode*> searchMoviesByActorFlexible(const String& actorName) {
        LinkedList<MovieNode*> results;
        String searchLower = actorName.toLower();
        
        // Get all actors
        LinkedList<String> allActorNames = actorTable.getKeys();
        
        // Find matching actors
        for (auto it = allActorNames.begin(); it != allActorNames.end(); ++it) {
            String currentActorLower = (*it).toLower();
            
            // Check if actor name contains search term
            if (currentActorLower.find(searchLower) != -1) {
                ActorNode** actorPtr = actorTable.search(*it);
                if (actorPtr != nullptr) {
                    LinkedList<MovieNode*> actorMovies = (*actorPtr)->getMovies();
                    // Add all movies from this actor
                    for (auto movieIt = actorMovies.begin(); movieIt != actorMovies.end(); ++movieIt) {
                        if (!results.contains(*movieIt)) {
                            results.append(*movieIt);
                        }
                    }
                }
            }
        }
        
        return results;
    }

    // Search movies by genre (exact match)
    LinkedList<MovieNode*> searchMoviesByGenre(const String& genreName) {
        LinkedList<MovieNode*> results;
        
        GenreNode** genrePtr = genreTable.search(genreName);
        if (genrePtr != nullptr) {
            return (*genrePtr)->getMovies();
        }
        
        return results;
    }

    // Search movies by genre (flexible - case insensitive)
    LinkedList<MovieNode*> searchMoviesByGenreFlexible(const String& genreName) {
        LinkedList<MovieNode*> results;
        String searchLower = genreName.toLower();
        
        // Get all genres
        LinkedList<String> allGenreNames = genreTable.getKeys();
        
        // Find matching genre
        for (auto it = allGenreNames.begin(); it != allGenreNames.end(); ++it) {
            String currentGenreLower = (*it).toLower();
            
            // Check if genre matches (exact or partial)
            if (currentGenreLower == searchLower || currentGenreLower.find(searchLower) != -1) {
                GenreNode** genrePtr = genreTable.search(*it);
                if (genrePtr != nullptr) {
                    return (*genrePtr)->getMovies();
                }
            }
        }
        
        return results;
    }

    // Search movies by director (exact match)
    LinkedList<MovieNode*> searchMoviesByDirector(const String& directorName) {
        LinkedList<MovieNode*> results;
        
        DirectorNode** directorPtr = directorTable.search(directorName);
        if (directorPtr != nullptr) {
            return (*directorPtr)->getMovies();
        }
        
        return results;
    }

    // Search movies by director (flexible - case insensitive and partial)
    LinkedList<MovieNode*> searchMoviesByDirectorFlexible(const String& directorName) {
        LinkedList<MovieNode*> results;
        String searchLower = directorName.toLower();
        
        // Get all directors
        LinkedList<String> allDirectorNames = directorTable.getKeys();
        
        // Find matching directors
        for (auto it = allDirectorNames.begin(); it != allDirectorNames.end(); ++it) {
            String currentDirectorLower = (*it).toLower();
            
            // Check if director name contains search term
            if (currentDirectorLower.find(searchLower) != -1) {
                DirectorNode** directorPtr = directorTable.search(*it);
                if (directorPtr != nullptr) {
                    LinkedList<MovieNode*> directorMovies = (*directorPtr)->getMovies();
                    // Add all movies from this director
                    for (auto movieIt = directorMovies.begin(); movieIt != directorMovies.end(); ++movieIt) {
                        if (!results.contains(*movieIt)) {
                            results.append(*movieIt);
                        }
                    }
                }
            }
        }
        
        return results;
    }

    // Search movies by year range
    LinkedList<MovieNode*> searchMoviesByYearRange(int startYear, int endYear) {
        LinkedList<MovieNode*> results;
        
        for (auto it = allMovies.begin(); it != allMovies.end(); ++it) {
            MovieNode* movie = *it;
            int year = movie->getYear();
            if (year >= startYear && year <= endYear) {
                results.append(movie);
            }
        }
        
        return results;
    }

    // Search movies by rating range
    LinkedList<MovieNode*> searchMoviesByRatingRange(double minRating, double maxRating) {
        LinkedList<MovieNode*> results;
        
        for (auto it = allMovies.begin(); it != allMovies.end(); ++it) {
            MovieNode* movie = *it;
            double rating = movie->getImdbScore();
            if (rating >= minRating && rating <= maxRating) {
                results.append(movie);
            }
        }
        
        return results;
    }

    // Get movie recommendations using BFS
    LinkedList<MovieNode*> getRecommendationsBFS(const String& movieTitle, int count = 10) {
        return graph.recommendMoviesBFS(movieTitle, count);
    }

    // Get movie recommendations using DFS
    LinkedList<MovieNode*> getRecommendationsDFS(const String& movieTitle, int count = 10) {
        return graph.recommendMoviesDFS(movieTitle, count);
    }

    // Find shortest path between two movies
    LinkedList<String> findMovieConnection(const String& movie1, const String& movie2) {
        return graph.findShortestPath(movie1, movie2);
    }

    // Get actor information (exact match)
    ActorNode* getActorInfo(const String& actorName) {
        ActorNode** actorPtr = actorTable.search(actorName);
        return (actorPtr != nullptr) ? *actorPtr : nullptr;
    }

    // Get actor information (flexible - case insensitive and partial)
    ActorNode* getActorInfoFlexible(const String& actorName) {
        String searchLower = actorName.toLower();
        
        // Get all actors
        LinkedList<String> allActorNames = actorTable.getKeys();
        
        // Find matching actor
        for (auto it = allActorNames.begin(); it != allActorNames.end(); ++it) {
            String currentActorLower = (*it).toLower();
            
            // Check if actor name contains search term
            if (currentActorLower.find(searchLower) != -1) {
                ActorNode** actorPtr = actorTable.search(*it);
                if (actorPtr != nullptr) {
                    return *actorPtr;
                }
            }
        }
        
        return nullptr;
    }

    // Get genre information (exact match)
    GenreNode* getGenreInfo(const String& genreName) {
        GenreNode** genrePtr = genreTable.search(genreName);
        return (genrePtr != nullptr) ? *genrePtr : nullptr;
    }

    // Get genre information (flexible - case insensitive)
    GenreNode* getGenreInfoFlexible(const String& genreName) {
        String searchLower = genreName.toLower();
        
        // Get all genres
        LinkedList<String> allGenreNames = genreTable.getKeys();
        
        // Find matching genre
        for (auto it = allGenreNames.begin(); it != allGenreNames.end(); ++it) {
            String currentGenreLower = (*it).toLower();
            
            // Check if genre matches
            if (currentGenreLower == searchLower || currentGenreLower.find(searchLower) != -1) {
                GenreNode** genrePtr = genreTable.search(*it);
                if (genrePtr != nullptr) {
                    return *genrePtr;
                }
            }
        }
        
        return nullptr;
    }

    // Get director information (exact match)
    DirectorNode* getDirectorInfo(const String& directorName) {
        DirectorNode** directorPtr = directorTable.search(directorName);
        return (directorPtr != nullptr) ? *directorPtr : nullptr;
    }

    // Get director information (flexible - case insensitive and partial)
    DirectorNode* getDirectorInfoFlexible(const String& directorName) {
        String searchLower = directorName.toLower();
        
        // Get all directors
        LinkedList<String> allDirectorNames = directorTable.getKeys();
        
        // Find matching director
        for (auto it = allDirectorNames.begin(); it != allDirectorNames.end(); ++it) {
            String currentDirectorLower = (*it).toLower();
            
            // Check if director name contains search term
            if (currentDirectorLower.find(searchLower) != -1) {
                DirectorNode** directorPtr = directorTable.search(*it);
                if (directorPtr != nullptr) {
                    return *directorPtr;
                }
            }
        }
        
        return nullptr;
    }

    // Display statistics
    void displayStatistics() {
        std::cout << "\n========================================" << std::endl;
        std::cout << "         DATASET STATISTICS" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Total Movies: " << totalMoviesLoaded << std::endl;
        std::cout << "Total Actors: " << actorTable.getSize() << std::endl;
        std::cout << "Total Genres: " << genreTable.getSize() << std::endl;
        std::cout << "Total Directors: " << directorTable.getSize() << std::endl;
        std::cout << "========================================" << std::endl;
    }

    // Get all genre names
    LinkedList<String> getAllGenres() {
        return genreTable.getKeys();
    }

    // Get all actor names
    LinkedList<String> getAllActors() {
        return actorTable.getKeys();
    }

    // Get all director names
    LinkedList<String> getAllDirectors() {
        return directorTable.getKeys();
    }
};
