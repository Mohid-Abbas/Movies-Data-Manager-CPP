#pragma once
#include "String.h"
#include "LinkedList.h"

// Forward declarations
class ActorNode;
class GenreNode;

// MovieNode class - represents a single movie
class MovieNode {
private:
    String title;
    String director;
    int year;
    double imdbScore;
    int duration;              // in minutes
    long long budget;
    long long gross;
    String contentRating;      // PG, PG-13, R, etc.
    String language;
    String country;
    String color;              // Color or Black & White
    int numVotedUsers;
    int numCriticReviews;
    int numUserReviews;
    double aspectRatio;
    int movieFacebookLikes;
    
    LinkedList<String> actors;     // List of actor names
    LinkedList<String> genres;     // List of genres
    LinkedList<String> plotKeywords;  // Plot keywords

public:
    // Constructor
    MovieNode() : year(0), imdbScore(0.0), duration(0), budget(0), gross(0),
                  numVotedUsers(0), numCriticReviews(0), numUserReviews(0),
                  aspectRatio(0.0), movieFacebookLikes(0) {}

    MovieNode(const String& movieTitle) : title(movieTitle), year(0), imdbScore(0.0),
                                          duration(0), budget(0), gross(0),
                                          numVotedUsers(0), numCriticReviews(0),
                                          numUserReviews(0), aspectRatio(0.0),
                                          movieFacebookLikes(0) {}

    // Setters
    void setTitle(const String& t) { title = t; }
    void setDirector(const String& d) { director = d; }
    void setYear(int y) { year = y; }
    void setImdbScore(double score) { imdbScore = score; }
    void setDuration(int d) { duration = d; }
    void setBudget(long long b) { budget = b; }
    void setGross(long long g) { gross = g; }
    void setContentRating(const String& cr) { contentRating = cr; }
    void setLanguage(const String& lang) { language = lang; }
    void setCountry(const String& c) { country = c; }
    void setColor(const String& col) { color = col; }
    void setNumVotedUsers(int n) { numVotedUsers = n; }
    void setNumCriticReviews(int n) { numCriticReviews = n; }
    void setNumUserReviews(int n) { numUserReviews = n; }
    void setAspectRatio(double ar) { aspectRatio = ar; }
    void setMovieFacebookLikes(int likes) { movieFacebookLikes = likes; }

    // Getters
    const String& getTitle() const { return title; }
    const String& getDirector() const { return director; }
    int getYear() const { return year; }
    double getImdbScore() const { return imdbScore; }
    int getDuration() const { return duration; }
    long long getBudget() const { return budget; }
    long long getGross() const { return gross; }
    const String& getContentRating() const { return contentRating; }
    const String& getLanguage() const { return language; }
    const String& getCountry() const { return country; }
    const String& getColor() const { return color; }
    int getNumVotedUsers() const { return numVotedUsers; }
    int getNumCriticReviews() const { return numCriticReviews; }
    int getNumUserReviews() const { return numUserReviews; }
    double getAspectRatio() const { return aspectRatio; }
    int getMovieFacebookLikes() const { return movieFacebookLikes; }

    // Actor management
    void addActor(const String& actorName) {
        if (!actorName.isEmpty()) {
            actors.append(actorName);
        }
    }

    const LinkedList<String>& getActors() const {
        return actors;
    }

    bool hasActor(const String& actorName) const {
        return actors.contains(actorName);
    }

    // Genre management
    void addGenre(const String& genreName) {
        if (!genreName.isEmpty()) {
            genres.append(genreName);
        }
    }

    const LinkedList<String>& getGenres() const {
        return genres;
    }

    bool hasGenre(const String& genreName) const {
        return genres.contains(genreName);
    }

    // Plot keywords management
    void addPlotKeyword(const String& keyword) {
        if (!keyword.isEmpty()) {
            plotKeywords.append(keyword);
        }
    }

    const LinkedList<String>& getPlotKeywords() const {
        return plotKeywords;
    }

    // Comparison operators (for AVL tree insertion based on title)
    bool operator<(const MovieNode& other) const {
        return title < other.title;
    }

    bool operator>(const MovieNode& other) const {
        return title > other.title;
    }

    bool operator==(const MovieNode& other) const {
        return title == other.title;
    }

    bool operator!=(const MovieNode& other) const {
        return title != other.title;
    }

    // Display movie information
    void display() const {
        std::cout << "========================================" << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Director: " << director << std::endl;
        std::cout << "Year: " << year << std::endl;
        std::cout << "IMDB Score: " << imdbScore << std::endl;
        std::cout << "Duration: " << duration << " minutes" << std::endl;
        
        if (budget > 0) {
            std::cout << "Budget: $" << budget << std::endl;
        }
        if (gross > 0) {
            std::cout << "Gross: $" << gross << std::endl;
        }
        
        std::cout << "Content Rating: " << contentRating << std::endl;
        std::cout << "Language: " << language << std::endl;
        std::cout << "Country: " << country << std::endl;

        std::cout << "Genres: ";
        for (auto it = genres.begin(); it != genres.end(); ++it) {
            std::cout << *it;
            auto next = it;
            ++next;
            if (next != genres.end()) std::cout << ", ";
        }
        std::cout << std::endl;

        std::cout << "Actors: ";
        for (auto it = actors.begin(); it != actors.end(); ++it) {
            std::cout << *it;
            auto next = it;
            ++next;
            if (next != actors.end()) std::cout << ", ";
        }
        std::cout << std::endl;

        if (!plotKeywords.isEmpty()) {
            std::cout << "Plot Keywords: ";
            for (auto it = plotKeywords.begin(); it != plotKeywords.end(); ++it) {
                std::cout << *it;
                auto next = it;
                ++next;
                if (next != plotKeywords.end()) std::cout << ", ";
            }
            std::cout << std::endl;
        }
        
        std::cout << "========================================" << std::endl;
    }

    // Display brief info (for lists)
    void displayBrief() const {
        std::cout << title << " (" << year << ") - " << imdbScore << "/10";
        if (!director.isEmpty()) {
            std::cout << " - Dir: " << director;
        }
        std::cout << std::endl;
    }
};
