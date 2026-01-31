#pragma once

// Common includes for the Movies Data Manager project
#include <iostream>
#include <fstream>

// Custom data structures (no STL allowed)
#include "String.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "AVLTree.h"
#include "HashTable.h"

// Domain model classes
#include "MovieNode.h"
#include "ActorNode.h"
#include "GenreNode.h"
#include "DirectorNode.h"

// Graph and utilities
#include "Graph.h"
#include "CSVParser.h"
#include "DataManager.h"

// Common constants
#define DEFAULT_HASH_TABLE_SIZE 100
#define MAX_RECOMMENDATIONS 10
