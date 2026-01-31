# Movies Data Manager - DSA Project

## Project Overview
A comprehensive Movies Data Manager system built in C++ without using STL (Standard Template Library). This project manages the IMDb 5000 Movie Dataset using custom implementations of advanced data structures including AVL Trees, Hash Tables, Linked Lists, Queues, Stacks, and Graphs.

## Features

### Data Structures Implemented (No STL)
- **String**: Custom string class with dynamic memory management
- **LinkedList**: Generic template-based linked list
- **Queue**: FIFO queue for BFS traversal
- **Stack**: LIFO stack for DFS traversal
- **AVL Tree**: Self-balancing binary search tree for movie storage
- **Hash Table**: Hash table with separate chaining for fast lookups
- **Graph**: Undirected graph for movie relationships

### Core Functionalities
1. **Search Operations**:
   - Search movie by exact title
   - Search movies by actor name
   - Search movies by genre
   - Search movies by director
   - Search movies by year range
   - Search movies by rating range

2. **Graph-Based Features**:
   - Movie recommendations using BFS (breadth-first search)
   - Movie recommendations using DFS (depth-first search)
   - Find shortest connection path between two movies
   - Connection strength analysis

3. **Information Display**:
   - View detailed movie information
   - View actor filmography and co-actors
   - View genre statistics and movie lists
   - View director statistics and filmography
   - Display dataset and graph statistics

## Project Structure

```
DSA_Project/
├── String.h              - Custom string implementation
├── LinkedList.h          - Generic linked list template
├── Queue.h               - Queue implementation
├── Stack.h               - Stack implementation
├── AVLTree.h             - AVL tree implementation
├── HashTable.h           - Hash table implementation
├── MovieNode.h           - Movie data structure
├── ActorNode.h           - Actor data structure
├── GenreNode.h           - Genre data structure
├── DirectorNode.h        - Director data structure
├── Graph.h               - Movie relationship graph
├── CSVParser.h           - CSV file parser
├── DataManager.h         - Central data management system
├── main.cpp              - Main application with menu interface
├── Source.h              - Common includes and definitions
└── sample_movies.csv     - Sample dataset for testing
```

## How to Build and Run

### Prerequisites
- C++ compiler (Visual Studio 2019/2022, g++, or clang++)
- IMDb 5000 Movie Dataset (CSV file)

### Building with Visual Studio
1. Open `DSA_Project.sln` in Visual Studio
2. Build the solution (Ctrl+Shift+B)
3. Run the project (F5 or Ctrl+F5)

### Building with g++ (Command Line)
```bash
g++ -std=c++11 main.cpp -o MovieManager.exe
```

### Running the Application
1. Run the executable
2. When prompted, enter the CSV filename (e.g., `sample_movies.csv` or `movie_metadata.csv`)
3. Wait for the dataset to load and graph to build
4. Use the menu to interact with the system

## Dataset

### Sample Dataset
A sample dataset (`sample_movies.csv`) with 13 movies is included for testing.

### Full Dataset
Download the full IMDb 5000 Movie Dataset from:
https://www.kaggle.com/datasets/carolzhangdc/imdb-5000-movie-dataset

Place the downloaded CSV file in the project directory.

## Usage Examples

### Example 1: Search for a Movie
```
Choice: 1
Enter movie title: Avatar
```
Output: Displays detailed information about Avatar including cast, genres, rating, etc.

### Example 2: Get Movie Recommendations
```
Choice: 7
Enter movie title: The Dark Knight Rises
How many recommendations? 5
```
Output: Lists 5 movies similar to The Dark Knight Rises based on shared actors/genres.

### Example 3: Find Connection Between Movies
```
Choice: 9
Enter first movie title: Avatar
Enter second movie title: Tangled
```
Output: Shows the shortest path connecting these movies through shared attributes.

### Example 4: View Actor Filmography
```
Choice: 10
Enter actor name: Tom Hardy
```
Output: Displays all movies featuring Tom Hardy and his co-actors.

## Implementation Details

### AVL Tree
- Self-balancing binary search tree
- Movies indexed by title
- O(log n) search, insert, and delete operations
- Automatic rebalancing using rotations

### Hash Table
- Separate chaining for collision resolution
- Dynamic resizing when load factor exceeds 0.75
- Custom hash function for string keys
- O(1) average-case lookup

### Graph
- Undirected graph representation
- Vertices: Movies
- Edges: Shared actors or genres
- BFS for shortest-path recommendations
- DFS for diverse recommendations

### Memory Management
- All data structures use dynamic memory allocation
- Proper destructors to prevent memory leaks
- RAII principles followed throughout

## Testing

### Test with Sample Dataset
```bash
# Use the included sample_movies.csv
Enter filename: sample_movies.csv
```

### Test Scenarios
1. Search for existing and non-existing movies
2. Search by various actors (e.g., "Tom Hardy", "Johnny Depp")
3. Search by genres (e.g., "Action", "Adventure")
4. Get recommendations for different movies
5. Find connections between related and unrelated movies
6. Test year and rating range searches

## Performance

- **Dataset Loading**: O(n) where n = number of movies
- **Graph Building**: O(n²) for edge creation (can be optimized)
- **Title Search**: O(log n) using AVL tree
- **Actor/Genre Search**: O(1) average using hash table
- **BFS Recommendations**: O(V + E) where V = vertices, E = edges
- **Shortest Path**: O(V + E) using BFS

## Project Requirements Met

✅ Custom String class (no std::string)
✅ LinkedList implementation
✅ Queue and Stack implementations
✅ AVL Tree for movie storage
✅ Hash Table for fast lookups
✅ Graph with BFS/DFS traversal
✅ CSV parsing and dataset loading
✅ All search functionalities
✅ Recommendation system
✅ Shortest path finding
✅ Menu-driven interface
✅ No STL usage
✅ Proper memory management
✅ Code documentation

## Future Enhancements

- Add partial title search (fuzzy matching)
- Implement weighted edges based on connection strength
- Add movie filtering by multiple criteria
- Export search results to file
- Add data visualization
- Implement more sophisticated recommendation algorithms

## Authors
- [Your Name]
- [Partner Name if applicable]

## Course Information
- **Course**: Data Structures and Algorithms
- **Semester**: Fall 2025
- **Institution**: FAST-NUCES
- **Department**: Artificial Intelligence and Data Science

## License
This project is created for educational purposes as part of the DSA course requirements.

## Acknowledgments
- IMDb for the movie dataset
- Course instructors and TAs
- Data Structures and Algorithms course materials
