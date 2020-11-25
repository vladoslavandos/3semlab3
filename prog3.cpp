#include <map>
#include "ParamQueueMethodsOnly.hpp"
typedef QueueElem<6> Param;
typedef ParamQueue<Param, 3> Queue;
typedef std::map<std::string, Queue> QueueMap;

void exit(QueueMap& qs, std::string& sel) { exit(0); }
void new_queue(QueueMap& qs, std::string& sel)
{
  std::cout << "Input queue name: ";
  std::string name;
  std::cin.get();
  std::getline(std::cin, name);
  std::cout << "Do you want to input params now?(0_/1) > ";
  char ch;
  std::cin >> ch;
  std::vector<Param> params{};
  while (ch == '1')
  {
    std::cout << "Input param (format: <number> <string>): ";
    params.push_back({});
    params.back().input();
    std::cout << "Do you want to continue?(0_/1) > ";
    std::cin >> ch;
  }
  qs[name] = Queue(params);
  sel      = name;
  std::cout << "Successfully created!";
}

void remove_queue(QueueMap& qs, std::string& sel)
{
  std::cout << "Input queue name: ";
  std::string name;
  std::cin.get();
  std::getline(std::cin, name);
  qs.erase(name);
  std::cout << "Successfully removed!";
}

void print_queue(QueueMap& qs, std::string& sel)
{
  qs[sel].output(std::cout << "Selected queue: \n");
}

void list_queues(QueueMap& qs, std::string& sel)
{
  for (auto& keyval : qs)
  {
    std::cout << keyval.first << (&*qs.rbegin() == &keyval ? "" : ", ");
  }
  std::cout << "\n";
}

void select_queue(QueueMap& qs, std::string& sel)
{
  std::cout << "Input queue name: ";
  std::string name;
  std::cin.get();
  std::getline(std::cin, name);
  if (qs.find(name) == qs.end())
  {
    std::cout << "Queue not found!";
    return;
  }
  sel = name;
  std::cout << "Queue '" << sel << "' selected!";
}

void add_params(QueueMap& qs, std::string& sel)
{
  char ch = '1';
  while (ch == '1')
  {
    std::cout << "Input param (format: <number> <string>): ";
    qs[sel].input();
    std::cout << "Do you want to continue?(0_/1) > ";
    std::cin >> ch;
  }
}

void pop_params(QueueMap& qs, std::string& sel)
{
  char ch = '1';
  while (ch == '1')
  {
    Param a;
    qs[sel].pop(a);
    a.output(std::cout << "Popped: ") << "\nDo you want to continue?(0_/1) > ";

    std::cin >> ch;
  }
}

void check_stat(QueueMap& qs, std::string& sel) { std::cout << "Queue status: " << qs[sel].check_state(); }


void (*options[])(QueueMap&, std::string&) = {exit,
                                              new_queue,
                                              remove_queue,
                                              list_queues,
                                              select_queue,
                                              print_queue,
                                              add_params,
                                              pop_params,
                                              check_stat,

};

int main()
{
  QueueMap queues;
  std::string selected = "numbers";
  queues["numbers"]    = Queue({{1, "one"}, {2, "two"}, {3, "three"}});

  while (1)
  {
    std::cout << "Ask... \n\
    [0]Exit\n\
    [1]New queue\n\
    [2]Remove queue\n\
    [3]List queues\n\
    [4]Select queue\n\
    [5]Print queue\n\
    [6]Add to queue\n\
    [7]Pop from queue\n\
    [8]Check queue status\n"
                 ">>";
    int choice;
    std::cin >> choice;
    if (choice > sizeof(options) / 8 - 1 || choice < 0)
    {
      std::cout << "Try again!\n";
      continue;
    }
    options[choice](queues, selected);
    std::cout << std::endl;
  }
}