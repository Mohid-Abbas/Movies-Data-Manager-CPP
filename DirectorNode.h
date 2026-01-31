#pragma once
#include "String.h"
#include "LinkedList.h"

// Forward declaration
class MovieNode;

// DirectorNode class - represents a director and their movies
class DirectorNode {
private:
    String directorName;
    LinkedList<MovieNode*> movies;  // List of pointers to movies
    int facebookLikes;

public:
    // Constructor
    DirectorNode() : facebookLikes(0) {}
    
    DirectorNode(const String& name) : directorName(name), facebookLikes(0) {}

    // Setters
    void setName(const String& name) { directorName = name; }
    void setFacebookLikes(int likes) { facebookLikes = likes; }

    // Getters
    const String& getName() const { return directorName; }
    int getFacebookLikes() const { return facebookLikes; }
    const LinkedList<MovieNode*>& getMovies() const { return movies; }

    // Add movie to director's filmography
    void addMovie(MovieNode* movie) {
        if (movie != nullptr) {
            movies.append(movie);
        }
    }

    // Get number of movies directed
    int getMovieCount() const {
        return movies.getSize();
    }

    // Get average rating of director's movies
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

    // Get total gross revenue
    long long getTotalGross() const {
        long long total = 0;
        
        for (auto it = movies.begin(); it != movies.end(); ++it) {
            MovieNode* movie = *it;
            total += movie->getGross();
        }
        
        return total;
    }

    // Display director information
    void display() const {
        std::cout << "========================================" << std::endl;
        std::cout << "Director: " << directorName << std::endl;
        std::cout << "Number of Movies: " << movies.getSize() << std::endl;
        std::cout << "Average Rating: " << getAverageRating() << "/10" << std::endl;
        std::cout << "Total Gross: $" << getTotalGross() << std::endl;
        if (facebookLikes > 0) {
            std::cout << "Facebook Likes: " << facebookLikes << std::endl;
        }
        std::cout << "========================================" << std::endl;
    }

    // Display director's filmography
    void displayFilmography() const {
        std::cout << "\nFilmography of " << directorName << ":" << std::endl;
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
    bool operator==(const DirectorNode& other) const {
        return directorName == other.directorName;
    }

    bool operator!=(const DirectorNode& other) const {
        return directorName != other.directorName;
    }
};
