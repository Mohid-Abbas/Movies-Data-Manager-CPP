#pragma once
#include "String.h"
#include "LinkedList.h"

// Forward declaration
class MovieNode;

// GenreNode class - represents a genre and movies in that genre
class GenreNode {
private:
    String genreName;
    LinkedList<MovieNode*> movies;  // List of pointers to movies

public:
    // Constructor
    GenreNode() {}
    
    GenreNode(const String& name) : genreName(name) {}

    // Setters
    void setName(const String& name) { genreName = name; }

    // Getters
    const String& getName() const { return genreName; }
    const LinkedList<MovieNode*>& getMovies() const { return movies; }

    // Add movie to genre
    void addMovie(MovieNode* movie) {
        if (movie != nullptr) {
            movies.append(movie);
        }
    }

    // Get number of movies in this genre
    int getMovieCount() const {
        return movies.getSize();
    }

    // Get average rating of movies in this genre
    double getAverageRating() const {
        if (movies.isEmpty()) return 0.0;
        
        double totalRating = 0.0;
        int count = 0;
        
        for (auto it = movies.begin(); it != movies.end(); ++it) {
            MovieNode* movie = *it;
            totalRating += movie->getImdbScore();
            count++;
        }
        
        return totalRating / count;
    }

    // Display genre information
    void display() const {
        std::cout << "========================================" << std::endl;
        std::cout << "Genre: " << genreName << std::endl;
        std::cout << "Number of Movies: " << movies.getSize() << std::endl;
        std::cout << "Average Rating: " << getAverageRating() << "/10" << std::endl;
        std::cout << "========================================" << std::endl;
    }

    // Display all movies in this genre
    void displayMovies() const {
        std::cout << "\nMovies in genre '" << genreName << "':" << std::endl;
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
    bool operator==(const GenreNode& other) const {
        return genreName == other.genreName;
    }

    bool operator!=(const GenreNode& other) const {
        return genreName != other.genreName;
    }
};
