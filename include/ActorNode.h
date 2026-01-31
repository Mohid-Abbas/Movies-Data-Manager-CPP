#pragma once
#include "String.h"
#include "LinkedList.h"

// Forward declaration
class MovieNode;

// ActorNode class - represents an actor and their filmography
class ActorNode {
private:
    String actorName;
    LinkedList<MovieNode*> movies;  // List of pointers to movies
    int totalFacebookLikes;

public:
    // Constructor
    ActorNode() : totalFacebookLikes(0) {}
    
    ActorNode(const String& name) : actorName(name), totalFacebookLikes(0) {}

    // Setters
    void setName(const String& name) { actorName = name; }
    void setFacebookLikes(int likes) { totalFacebookLikes = likes; }

    // Getters
    const String& getName() const { return actorName; }
    int getFacebookLikes() const { return totalFacebookLikes; }
    const LinkedList<MovieNode*>& getMovies() const { return movies; }

    // Add movie to filmography
    void addMovie(MovieNode* movie) {
        if (movie != nullptr) {
            movies.append(movie);
        }
    }

    // Get number of movies
    int getMovieCount() const {
        return movies.getSize();
    }

    // Get co-actors (actors who appeared in same movies)
    LinkedList<String> getCoActors() const {
        LinkedList<String> coActors;
        
        for (auto it = movies.begin(); it != movies.end(); ++it) {
            MovieNode* movie = *it;
            const LinkedList<String>& actors = movie->getActors();
            
            for (auto actorIt = actors.begin(); actorIt != actors.end(); ++actorIt) {
                const String& actor = *actorIt;
                if (actor != actorName && !coActors.contains(actor)) {
                    coActors.append(actor);
                }
            }
        }
        
        return coActors;
    }

    // Display actor information
    void display() const {
        std::cout << "========================================" << std::endl;
        std::cout << "Actor: " << actorName << std::endl;
        std::cout << "Number of Movies: " << movies.getSize() << std::endl;
        if (totalFacebookLikes > 0) {
            std::cout << "Facebook Likes: " << totalFacebookLikes << std::endl;
        }
        std::cout << "========================================" << std::endl;
    }

    // Display filmography
    void displayFilmography() const {
        std::cout << "\nFilmography of " << actorName << ":" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        
        int count = 1;
        for (auto it = movies.begin(); it != movies.end(); ++it) {
            MovieNode* movie = *it;
            std::cout << count++ << ". ";
            movie->displayBrief();
        }
        
        if (movies.isEmpty()) {
            std::cout << "No movies found." << std::endl;
        }
    }

    // Comparison operators
    bool operator==(const ActorNode& other) const {
        return actorName == other.actorName;
    }

    bool operator!=(const ActorNode& other) const {
        return actorName != other.actorName;
    }
};
