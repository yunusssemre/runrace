#include <iostream>
#include <chrono>
#include <random> 
#include <mutex> 

#include "thread_safe_random.hpp"

// Defines an engine

std::mt19937_64 my_rng; 
// adjust speed 1-5 random
std::uniform_real_distribution<double> my_unif_real_dist(1.0, 5.0); 
std::mutex my_rng_mutex; // a mutex to guard my_rng


double RANDOM() {
    std::lock_guard<std::mutex> lock(my_rng_mutex);
    return my_unif_real_dist(my_rng);
    // mutex is released when lock goes out of scope
}

//Function to seed the random number generator from main fileThis function again locks the mutex for when a thread decides to re-seed the RNG.
 

void Seed(int seed) {
    std::lock_guard<std::mutex> lock(my_rng_mutex);
    my_rng.seed(seed);
    // mutex is released when lock goes out of scope
}
