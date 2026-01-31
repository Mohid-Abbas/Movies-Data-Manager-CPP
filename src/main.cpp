#include <iostream>
#include "DataManager.h"
#include "String.h"

using namespace std;

// Display main menu
void displayMenu() {
    cout << "\n========================================" << endl;
    cout << "   MOVIES DATA MANAGER - MAIN MENU" << endl;
    cout << "========================================" << endl;
    cout << "1.  Search movie by title" << endl;
    cout << "2.  Search movies by actor" << endl;
    cout << "3.  Search movies by genre" << endl;
    cout << "4.  Search movies by director" << endl;
    cout << "5.  Search movies by year range" << endl;
    cout << "6.  Search movies by rating range" << endl;
    cout << "7.  Get movie recommendations (BFS)" << endl;
    cout << "8.  Get movie recommendations (DFS)" << endl;
    cout << "9.  Find connection between two movies" << endl;
    cout << "10. View actor information" << endl;
    cout << "11. View genre information" << endl;
    cout << "12. View director information" << endl;
    cout << "13. Display dataset statistics" << endl;
    cout << "14. Display graph statistics" << endl;
    cout << "0.  Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice: ";
}

// Read a line of input into a String
String readLine() {
    char buffer[1024];
    cin.getline(buffer, sizeof(buffer));
    return String(buffer);
}

int main() {
    DataManager dataManager;
    
    cout << "========================================" << endl;
    cout << "  MOVIES DATA MANAGER SYSTEM" << endl;
    cout << "========================================\n" << endl;

    // Load dataset
    cout << "Please enter the CSV filename (e.g., movie_metadata.csv): ";
    String filename = readLine();
    
    if (!dataManager.loadFromCSV(filename.c_str())) {
        cout << "Failed to load dataset. Exiting..." << endl;
        return 1;
    }

    // Build graph
    dataManager.buildGraph();

    // Main menu loop
    bool running = true;
    while (running) {
        displayMenu();
        
        int choice;
        cin >> choice;
        cin.ignore();  // Clear newline

        switch (choice) {
            case 1: {
                // Search by title
                cout << "\nEnter movie title: ";
                String title = readLine();
                
                MovieNode* movie = dataManager.searchMovieByTitleFlexible(title);
                if (movie != nullptr) {
                    cout << "\nMovie found:\n";
                    movie->display();
                } else {
                    cout << "\nMovie not found." << endl;
                    cout << "Tip: Try searching with partial title (e.g., 'dark knight' or 'avatar')" << endl;
                }
                break;
            }

            case 2: {
                // Search by actor
                cout << "\nEnter actor name: ";
                String actorName = readLine();
                
                LinkedList<MovieNode*> movies = dataManager.searchMoviesByActorFlexible(actorName);
                
                if (!movies.isEmpty()) {
                    cout << "\nMovies featuring actors matching '" << actorName << "':" << endl;
                    cout << "----------------------------------------" << endl;
                    int count = 1;
                    for (auto it = movies.begin(); it != movies.end(); ++it) {
                        cout << count++ << ". ";
                        (*it)->displayBrief();
                    }
                } else {
                    cout << "\nNo movies found for this actor." << endl;
                    cout << "Tip: Try partial name (e.g., 'tom' for 'Tom Hardy')" << endl;
                }
                break;
            }

            case 3: {
                // Search by genre
                cout << "\nEnter genre name: ";
                String genreName = readLine();
                
                LinkedList<MovieNode*> movies = dataManager.searchMoviesByGenreFlexible(genreName);
                
                if (!movies.isEmpty()) {
                    cout << "\nMovies in genre matching '" << genreName << "':" << endl;
                    cout << "----------------------------------------" << endl;
                    int count = 1;
                    for (auto it = movies.begin(); it != movies.end(); ++it) {
                        cout << count++ << ". ";
                        (*it)->displayBrief();
                        if (count > 20) {
                            cout << "... and " << (movies.getSize() - 20) << " more." << endl;
                            break;
                        }
                    }
                } else {
                    cout << "\nNo movies found for this genre." << endl;
                    cout << "Tip: Try 'action', 'comedy', 'drama', etc." << endl;
                }
                break;
            }

            case 4: {
                // Search by director
                cout << "\nEnter director name: ";
                String directorName = readLine();
                
                LinkedList<MovieNode*> movies = dataManager.searchMoviesByDirectorFlexible(directorName);
                
                if (!movies.isEmpty()) {
                    cout << "\nMovies by directors matching '" << directorName << "':" << endl;
                    cout << "----------------------------------------" << endl;
                    int count = 1;
                    for (auto it = movies.begin(); it != movies.end(); ++it) {
                        cout << count++ << ". ";
                        (*it)->displayBrief();
                    }
                } else {
                    cout << "\nNo movies found for this director." << endl;
                    cout << "Tip: Try partial name (e.g., 'nolan' for 'Christopher Nolan')" << endl;
                }
                break;
            }

            case 5: {
                // Search by year range
                cout << "\nEnter start year: ";
                int startYear;
                cin >> startYear;
                
                cout << "Enter end year: ";
                int endYear;
                cin >> endYear;
                cin.ignore();
                
                LinkedList<MovieNode*> movies = dataManager.searchMoviesByYearRange(startYear, endYear);
                
                if (!movies.isEmpty()) {
                    cout << "\nMovies from " << startYear << " to " << endYear << ":" << endl;
                    cout << "----------------------------------------" << endl;
                    int count = 1;
                    for (auto it = movies.begin(); it != movies.end(); ++it) {
                        cout << count++ << ". ";
                        (*it)->displayBrief();
                        if (count > 20) {
                            cout << "... and " << (movies.getSize() - 20) << " more." << endl;
                            break;
                        }
                    }
                } else {
                    cout << "\nNo movies found in this year range." << endl;
                }
                break;
            }

            case 6: {
                // Search by rating range
                cout << "\nEnter minimum rating (0-10): ";
                double minRating;
                cin >> minRating;
                
                cout << "Enter maximum rating (0-10): ";
                double maxRating;
                cin >> maxRating;
                cin.ignore();
                
                LinkedList<MovieNode*> movies = dataManager.searchMoviesByRatingRange(minRating, maxRating);
                
                if (!movies.isEmpty()) {
                    cout << "\nMovies with rating between " << minRating << " and " << maxRating << ":" << endl;
                    cout << "----------------------------------------" << endl;
                    int count = 1;
                    for (auto it = movies.begin(); it != movies.end(); ++it) {
                        cout << count++ << ". ";
                        (*it)->displayBrief();
                        if (count > 20) {
                            cout << "... and " << (movies.getSize() - 20) << " more." << endl;
                            break;
                        }
                    }
                } else {
                    cout << "\nNo movies found in this rating range." << endl;
                }
                break;
            }

            case 7: {
                // Recommendations using BFS
                cout << "\nEnter movie title: ";
                String title = readLine();
                
                // Find the exact title first
                MovieNode* movie = dataManager.searchMovieByTitleFlexible(title);
                if (movie == nullptr) {
                    cout << "\nMovie not found. Cannot get recommendations." << endl;
                    break;
                }
                
                String exactTitle = movie->getTitle();
                cout << "Getting recommendations for: " << exactTitle << endl;
                
                cout << "How many recommendations? (default 10): ";
                int count = 10;
                cin >> count;
                cin.ignore();
                
                LinkedList<MovieNode*> recommendations = dataManager.getRecommendationsBFS(exactTitle, count);
                
                if (!recommendations.isEmpty()) {
                    cout << "\nRecommended movies (BFS - similar movies):" << endl;
                    cout << "----------------------------------------" << endl;
                    int num = 1;
                    for (auto it = recommendations.begin(); it != recommendations.end(); ++it) {
                        cout << num++ << ". ";
                        (*it)->displayBrief();
                    }
                } else {
                    cout << "\nNo recommendations found. Movie may not exist or has no connections." << endl;
                }
                break;
            }

            case 8: {
                // Recommendations using DFS
                cout << "\nEnter movie title: ";
                String title = readLine();
                
                // Find the exact title first
                MovieNode* movie = dataManager.searchMovieByTitleFlexible(title);
                if (movie == nullptr) {
                    cout << "\nMovie not found. Cannot get recommendations." << endl;
                    break;
                }
                
                String exactTitle = movie->getTitle();
                cout << "Getting recommendations for: " << exactTitle << endl;
                
                cout << "How many recommendations? (default 10): ";
                int count = 10;
                cin >> count;
                cin.ignore();
                
                LinkedList<MovieNode*> recommendations = dataManager.getRecommendationsDFS(exactTitle, count);
                
                if (!recommendations.isEmpty()) {
                    cout << "\nRecommended movies (DFS - diverse exploration):" << endl;
                    cout << "----------------------------------------" << endl;
                    int num = 1;
                    for (auto it = recommendations.begin(); it != recommendations.end(); ++it) {
                        cout << num++ << ". ";
                        (*it)->displayBrief();
                    }
                } else {
                    cout << "\nNo recommendations found. Movie may not exist or has no connections." << endl;
                }
                break;
            }

            case 9: {
                // Find connection between movies
                cout << "\nEnter first movie title: ";
                String movie1Input = readLine();
                
                cout << "Enter second movie title: ";
                String movie2Input = readLine();
                
                // Find exact titles
                MovieNode* m1 = dataManager.searchMovieByTitleFlexible(movie1Input);
                MovieNode* m2 = dataManager.searchMovieByTitleFlexible(movie2Input);
                
                if (m1 == nullptr || m2 == nullptr) {
                    cout << "\nOne or both movies not found." << endl;
                    break;
                }
                
                String movie1 = m1->getTitle();
                String movie2 = m2->getTitle();
                
                LinkedList<String> path = dataManager.findMovieConnection(movie1, movie2);
                
                if (!path.isEmpty()) {
                    cout << "\nConnection path found:" << endl;
                    cout << "----------------------------------------" << endl;
                    int step = 1;
                    for (auto it = path.begin(); it != path.end(); ++it) {
                        cout << step++ << ". " << *it << endl;
                    }
                    cout << "\nPath length: " << (path.getSize() - 1) << " steps" << endl;
                } else {
                    cout << "\nNo connection found between these movies." << endl;
                }
                break;
            }

            case 10: {
                // View actor information
                cout << "\nEnter actor name: ";
                String actorName = readLine();
                
                ActorNode* actor = dataManager.getActorInfoFlexible(actorName);
                if (actor != nullptr) {
                    actor->display();
                    actor->displayFilmography();
                } else {
                    cout << "\nActor not found." << endl;
                    cout << "Tip: Try partial name (e.g., 'tom' or 'hardy')" << endl;
                }
                break;
            }

            case 11: {
                // View genre information
                cout << "\nEnter genre name: ";
                String genreName = readLine();
                
                GenreNode* genre = dataManager.getGenreInfoFlexible(genreName);
                if (genre != nullptr) {
                    genre->display();
                    
                    cout << "\nShow all movies in this genre? (y/n): ";
                    char choice;
                    cin >> choice;
                    cin.ignore();
                    
                    if (choice == 'y' || choice == 'Y') {
                        genre->displayMovies();
                    }
                } else {
                    cout << "\nGenre not found." << endl;
                    cout << "Tip: Try 'action', 'comedy', 'drama', 'thriller', etc." << endl;
                }
                break;
            }

            case 12: {
                // View director information
                cout << "\nEnter director name: ";
                String directorName = readLine();
                
                DirectorNode* director = dataManager.getDirectorInfoFlexible(directorName);
                if (director != nullptr) {
                    director->display();
                    director->displayFilmography();
                } else {
                    cout << "\nDirector not found." << endl;
                    cout << "Tip: Try partial name (e.g., 'nolan' or 'cameron')" << endl;
                }
                break;
            }

            case 13: {
                // Display statistics
                dataManager.displayStatistics();
                break;
            }

            case 14: {
                // Display graph statistics
                // Already displayed during graph building, but can show again
                cout << "\nGraph statistics are displayed during initialization." << endl;
                dataManager.displayStatistics();
                break;
            }

            case 0: {
                // Exit
                cout << "\nThank you for using Movies Data Manager!" << endl;
                cout << "Goodbye!" << endl;
                running = false;
                break;
            }

            default: {
                cout << "\nInvalid choice. Please try again." << endl;
                break;
            }
        }

        if (running) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }

    return 0;
}
