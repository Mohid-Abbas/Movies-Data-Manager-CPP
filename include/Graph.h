#pragma once
#include "MovieNode.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "HashTable.h"
#include <iostream>

// Graph class for movie relationships
class MovieGraph {
private:
    // Graph vertex representing a movie
    struct Vertex {
        MovieNode* movie;
        LinkedList<Vertex*> adjacentVertices;  // Connected movies
        
        Vertex(MovieNode* m) : movie(m) {}
    };

    LinkedList<Vertex*> vertices;
    HashTable<String, Vertex*> vertexMap;  // Map movie title to vertex

    // Find vertex by movie title
    Vertex* findVertex(const String& movieTitle) {
        Vertex** vertexPtr = vertexMap.search(movieTitle);
        return (vertexPtr != nullptr) ? *vertexPtr : nullptr;
    }

    // Check if two movies share actors or genres
    bool areMoviesRelated(MovieNode* movie1, MovieNode* movie2) {
        // Check shared actors
        const LinkedList<String>& actors1 = movie1->getActors();
        const LinkedList<String>& actors2 = movie2->getActors();
        
        for (auto it1 = actors1.begin(); it1 != actors1.end(); ++it1) {
            for (auto it2 = actors2.begin(); it2 != actors2.end(); ++it2) {
                if (*it1 == *it2) {
                    return true;
                }
            }
        }

        // Check shared genres
        const LinkedList<String>& genres1 = movie1->getGenres();
        const LinkedList<String>& genres2 = movie2->getGenres();
        
        for (auto it1 = genres1.begin(); it1 != genres1.end(); ++it1) {
            for (auto it2 = genres2.begin(); it2 != genres2.end(); ++it2) {
                if (*it1 == *it2) {
                    return true;
                }
            }
        }

        return false;
    }

public:
    // Constructor
    MovieGraph() {}

    // Destructor
    ~MovieGraph() {
        for (auto it = vertices.begin(); it != vertices.end(); ++it) {
            delete *it;
        }
    }

    // Add movie as vertex
    void addMovie(MovieNode* movie) {
        if (movie == nullptr) return;

        const String& title = movie->getTitle();
        if (vertexMap.contains(title)) return;  // Already exists

        Vertex* newVertex = new Vertex(movie);
        vertices.append(newVertex);
        vertexMap.insert(title, newVertex);
    }

    // Build edges between related movies
    void buildEdges() {
        // For each pair of movies, check if they're related
        for (auto it1 = vertices.begin(); it1 != vertices.end(); ++it1) {
            Vertex* v1 = *it1;
            
            auto it2 = it1;
            ++it2;
            
            for (; it2 != vertices.end(); ++it2) {
                Vertex* v2 = *it2;
                
                if (areMoviesRelated(v1->movie, v2->movie)) {
                    // Add edge in both directions (undirected graph)
                    v1->adjacentVertices.append(v2);
                    v2->adjacentVertices.append(v1);
                }
            }
        }
    }

    // BFS-based movie recommendations
    LinkedList<MovieNode*> recommendMoviesBFS(const String& movieTitle, int maxRecommendations = 10) {
        LinkedList<MovieNode*> recommendations;
        
        Vertex* startVertex = findVertex(movieTitle);
        if (startVertex == nullptr) return recommendations;

        // Track visited vertices
        HashTable<String, bool> visited;
        Queue<Vertex*> queue;

        visited.insert(movieTitle, true);
        queue.enqueue(startVertex);

        while (!queue.isEmpty() && recommendations.getSize() < maxRecommendations) {
            Vertex* current = queue.dequeue();

            // Add adjacent movies to recommendations
            for (auto it = current->adjacentVertices.begin(); 
                 it != current->adjacentVertices.end(); ++it) {
                Vertex* adjacent = *it;
                const String& adjTitle = adjacent->movie->getTitle();

                if (!visited.contains(adjTitle)) {
                    visited.insert(adjTitle, true);
                    queue.enqueue(adjacent);
                    
                    if (recommendations.getSize() < maxRecommendations) {
                        recommendations.append(adjacent->movie);
                    }
                }
            }
        }

        return recommendations;
    }

    // DFS-based movie recommendations
    LinkedList<MovieNode*> recommendMoviesDFS(const String& movieTitle, int maxRecommendations = 10) {
        LinkedList<MovieNode*> recommendations;
        
        Vertex* startVertex = findVertex(movieTitle);
        if (startVertex == nullptr) return recommendations;

        // Track visited vertices
        HashTable<String, bool> visited;
        Stack<Vertex*> stack;

        visited.insert(movieTitle, true);
        stack.push(startVertex);

        while (!stack.isEmpty() && recommendations.getSize() < maxRecommendations) {
            Vertex* current = stack.pop();

            // Add adjacent movies to recommendations
            for (auto it = current->adjacentVertices.begin(); 
                 it != current->adjacentVertices.end(); ++it) {
                Vertex* adjacent = *it;
                const String& adjTitle = adjacent->movie->getTitle();

                if (!visited.contains(adjTitle)) {
                    visited.insert(adjTitle, true);
                    stack.push(adjacent);
                    
                    if (recommendations.getSize() < maxRecommendations) {
                        recommendations.append(adjacent->movie);
                    }
                }
            }
        }

        return recommendations;
    }

    // Find shortest path between two movies
    LinkedList<String> findShortestPath(const String& startTitle, const String& endTitle) {
        LinkedList<String> path;
        
        Vertex* startVertex = findVertex(startTitle);
        Vertex* endVertex = findVertex(endTitle);
        
        if (startVertex == nullptr || endVertex == nullptr) {
            return path;
        }

        // BFS with parent tracking
        HashTable<String, bool> visited;
        HashTable<String, String> parent;
        Queue<Vertex*> queue;

        visited.insert(startTitle, true);
        queue.enqueue(startVertex);

        bool found = false;

        while (!queue.isEmpty() && !found) {
            Vertex* current = queue.dequeue();
            const String& currentTitle = current->movie->getTitle();

            if (currentTitle == endTitle) {
                found = true;
                break;
            }

            for (auto it = current->adjacentVertices.begin(); 
                 it != current->adjacentVertices.end(); ++it) {
                Vertex* adjacent = *it;
                const String& adjTitle = adjacent->movie->getTitle();

                if (!visited.contains(adjTitle)) {
                    visited.insert(adjTitle, true);
                    parent.insert(adjTitle, currentTitle);
                    queue.enqueue(adjacent);
                }
            }
        }

        if (!found) {
            return path;  // No path found
        }

        // Reconstruct path from end to start
        Stack<String> reversePath;
        String current = endTitle;
        
        while (current != startTitle) {
            reversePath.push(current);
            String* parentPtr = parent.search(current);
            if (parentPtr == nullptr) break;
            current = *parentPtr;
        }
        reversePath.push(startTitle);

        // Reverse the path
        while (!reversePath.isEmpty()) {
            path.append(reversePath.pop());
        }

        return path;
    }

    // Get connection strength between two movies (number of shared attributes)
    int getConnectionStrength(const String& title1, const String& title2) {
        Vertex* v1 = findVertex(title1);
        Vertex* v2 = findVertex(title2);
        
        if (v1 == nullptr || v2 == nullptr) return 0;

        int strength = 0;
        MovieNode* m1 = v1->movie;
        MovieNode* m2 = v2->movie;

        // Count shared actors
        const LinkedList<String>& actors1 = m1->getActors();
        const LinkedList<String>& actors2 = m2->getActors();
        
        for (auto it1 = actors1.begin(); it1 != actors1.end(); ++it1) {
            for (auto it2 = actors2.begin(); it2 != actors2.end(); ++it2) {
                if (*it1 == *it2) strength++;
            }
        }

        // Count shared genres
        const LinkedList<String>& genres1 = m1->getGenres();
        const LinkedList<String>& genres2 = m2->getGenres();
        
        for (auto it1 = genres1.begin(); it1 != genres1.end(); ++it1) {
            for (auto it2 = genres2.begin(); it2 != genres2.end(); ++it2) {
                if (*it1 == *it2) strength++;
            }
        }

        return strength;
    }

    // Display graph statistics
    void displayStatistics() const {
        std::cout << "========================================" << std::endl;
        std::cout << "Movie Graph Statistics" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Total Movies (Vertices): " << vertices.getSize() << std::endl;
        
        int totalEdges = 0;
        for (auto it = vertices.begin(); it != vertices.end(); ++it) {
            Vertex* v = *it;
            totalEdges += v->adjacentVertices.getSize();
        }
        totalEdges /= 2;  // Each edge counted twice
        
        std::cout << "Total Connections (Edges): " << totalEdges << std::endl;
        std::cout << "========================================" << std::endl;
    }
};
