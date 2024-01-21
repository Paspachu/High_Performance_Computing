#include <iostream>
#include <thread>
#include <random>
#include <queue>

// Global constant variables
const int ELEVATORS = 3;
const int FLOORS = 20;
const int APARTMENTS_PER_FLOOR = 10;
const int MAX_PEOPLE = 5; //per elevator at one time
const int MAX_WAIT_TIME = 5000; // milliseconds

// Global variables
int people_serviced = 0;
std::mutex cout_mutex, queue_mutex, serviced_mutex;
std::condition_variable queue_cv;
std::vector<std::queue<int>> elevators(ELEVATORS), starts(ELEVATORS), ends(ELEVATORS);
std::vector<int> currfloors(ELEVATORS), directions(ELEVATORS);


// Return random integer in between min and max
int intRand(const int min, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min,max);
    return dist(gen);
}

void person(int id)
{
    // Randomly choose the start floor and the end floor for the person.
    int start = intRand(1, FLOORS);
    int end = intRand(1, FLOORS);
    // If the start floor and the end floor is the same, rechoose.
    while (start == end)
    {
        start = intRand(1, FLOORS);
        end = intRand(1, FLOORS);
    }

    // Print out the start floor and the end floor of the person.
    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex);
        std::cout << "Person " << id << " wants to go from floor " << start << " to floor " << end << std::endl;
    }
    
    // Choose the best elevator for this person based on the distance between the person and the elevators
    int best_choice = 0;
    int min_distance = FLOORS;
    for (int i = 0; i < ELEVATORS; i++)
    {
        int standard = std::abs(start - currfloors[i]);
        if (standard < min_distance)
        {
            min_distance = std::abs(start - currfloors[i]);
            best_choice = i;
        }
    }

    // Add the person and destinations to the selected elevator
    {
        std::unique_lock<std::mutex> queue_lock(queue_mutex);
        elevators[best_choice].push(id);
        starts[best_choice].push(start);
        ends[best_choice].push(end);
    }
}

void elevator(int id, int &num_people)
{
    std::queue<int> &elevator_queue = elevators[id];
    std::queue<int> &start_floor = starts[id];
    std::queue<int> &end_floor = ends[id];
    int &currfloor = currfloors[id];
    int &direction = directions[id];
    int total_users = 0;
    
    // End when all people are serviced
    while (people_serviced != num_people)
    {
        std::unique_lock<std::mutex> queue_lock(queue_mutex);
        if (elevator_queue.empty())
        {
            continue;
        }
        
        // Move elevator from its current floor to where the person is
        int person_id = std::move(elevator_queue.front());
        int start = std::move(start_floor.front());
        {
            std::lock_guard<std::mutex> cout_lock(cout_mutex);
            std::cout << "Elevator " << id << " moving from floor " << currfloor << " to floor " << start << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "Person " << person_id << " entered Elevator " << id << "\n";
        }
        direction = (start - currfloor > 0) ? 1 : -1;
        currfloor = start;
        start_floor.pop();

        // Move elevator from the person's starting floor to the ending floor
        int end = std::move(end_floor.front());
        {
            std::lock_guard<std::mutex> cout_lock(cout_mutex);
            std::cout << "Elevator " << id << " moving from floor " << currfloor << " to floor " << end << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "Person " << person_id << " exited Elevator " << id << "\n";
        }
        direction = (end - currfloor > 0) ? 1 : -1;
        currfloor = end;
        end_floor.pop();
        
        // Remove person from the queue
        elevator_queue.pop();

        // Increase number of people who used the elevator and the number of total people serviced.
        total_users++;
        {
            std::unique_lock<std::mutex> serviced_lock(serviced_mutex);
            people_serviced++;
        }
    }

    // Print out the total number of people who used the elevator
    std::lock_guard<std::mutex> cout_lock(cout_mutex);
    std::cout << "Elevator " << id << " serviced " << total_users << " people" << std::endl;
}



int main(int argc, char **argv)
{
    // Take the number of people to service as an input
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " num_people" << std::endl;
        return 1;
    }
    int num_people = std::atoi(argv[1]);

    // Initialize currfloors and directions vectors
    for (int i = 0; i < ELEVATORS; i++)
    {
        currfloors[i] = 1;
        directions[i] = 1; // -1: DOWN, 1: UP
    }

    // Start the elevator threads
    std::thread elevator0_thread(elevator, 0, std::ref(num_people));
    std::thread elevator1_thread(elevator, 1, std::ref(num_people));
    std::thread elevator2_thread(elevator, 2, std::ref(num_people));

    // Detach the person threads after random seconds
    for (int i = 0; i < num_people; i++)
    {
        int wait_time = intRand(0, MAX_WAIT_TIME);
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
        std::thread(person, i).detach();
    }

    // Join the elevator threads
    elevator0_thread.join();
    elevator1_thread.join();
    elevator2_thread.join();

    // Print out the end of the service
    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex);
        std::cout << "All people serviced!" << std::endl;
    }

    return 0;
}