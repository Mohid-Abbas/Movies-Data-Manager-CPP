# Quick Start Guide - Movies Data Manager

## Build Instructions

### Option 1: Visual Studio (Recommended)
1. Open `DSA_Project.sln` in Visual Studio
2. Select **Debug** or **Release** configuration
3. Press **Ctrl+Shift+B** to build
4. Press **F5** to run with debugging, or **Ctrl+F5** to run without debugging

### Option 2: Command Line (g++)
```bash
cd c:\DSA_Project\DSA_Project
g++ -std=c++11 main.cpp -o MovieManager.exe
MovieManager.exe
```

### Option 3: Command Line (cl.exe - MSVC)
```bash
# Open "Developer Command Prompt for VS"
cd c:\DSA_Project\DSA_Project
cl /EHsc /std:c++14 main.cpp /Fe:MovieManager.exe
MovieManager.exe
```

## First Run

1. When prompted, enter: `sample_movies.csv`
2. Wait for dataset to load (should be instant for 13 movies)
3. Wait for graph to build
4. Use the menu to explore features

## Quick Test Scenarios

### Scenario 1: Basic Search
```
Choice: 1
Enter movie title: Avatar
```
Should display full Avatar movie details.

### Scenario 2: Actor Search
```
Choice: 2
Enter actor name: Tom Hardy
```
Should show "The Dark Knight Rises".

### Scenario 3: Genre Search
```
Choice: 3
Enter genre name: Action
```
Should list all action movies.

### Scenario 4: Recommendations
```
Choice: 7
Enter movie title: Avatar
How many recommendations? 5
```
Should recommend similar sci-fi/action movies.

### Scenario 5: Movie Connection
```
Choice: 9
Enter first movie title: Avatar
Enter second movie title: The Dark Knight Rises
```
Should show connection path through shared attributes.

## Common Issues

### Issue: "File not found"
**Solution**: Make sure `sample_movies.csv` is in the same directory as the executable, or provide the full path.

### Issue: "Movie not found"
**Solution**: Movie titles must match exactly. Try:
- `Avatar ` (with trailing space as in CSV)
- `The Dark Knight Rises ` (with trailing space)

### Issue: Compilation errors
**Solution**: 
- Ensure all .h files are in the same directory
- Use C++11 or later standard
- Check that no STL headers are accidentally included

## Testing with Full Dataset

1. Download from: https://www.kaggle.com/datasets/carolzhangdc/imdb-5000-movie-dataset
2. Save as `movie_metadata.csv` in project directory
3. Run program and enter: `movie_metadata.csv`
4. Wait for loading (may take 10-30 seconds for graph building)
5. Test all features with real movie data

## Sample Movie Titles in Test Dataset

Use these exact titles (with trailing space):
- `Avatar `
- `The Dark Knight Rises `
- `Spectre `
- `Spider-Man 3 `
- `Tangled `
- `Avengers: Age of Ultron `
- `Harry Potter and the Half-Blood Prince `
- `Batman v Superman: Dawn of Justice `

## Sample Actor Names

- `Tom Hardy`
- `Johnny Depp`
- `Christian Bale`
- `Robert Downey Jr.`
- `Daniel Radcliffe`

## Sample Genres

- `Action`
- `Adventure`
- `Sci-Fi`
- `Fantasy`
- `Thriller`
- `Animation`
- `Comedy`

## Sample Directors

- `James Cameron`
- `Christopher Nolan`
- `Joss Whedon`
- `Sam Mendes`

## Performance Expectations

### Sample Dataset (13 movies)
- Loading: < 1 second
- Graph building: < 1 second
- All searches: Instant

### Full Dataset (~5000 movies)
- Loading: 3-5 seconds
- Graph building: 20-40 seconds
- Title search: < 0.01 seconds
- Actor/Genre search: < 0.01 seconds
- Recommendations: < 1 second

## Memory Usage

### Sample Dataset
- ~1-2 MB

### Full Dataset
- ~50-100 MB (depends on graph density)

## Exit

Press `0` to exit the program gracefully.
All memory will be cleaned up automatically.
