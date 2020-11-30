#include <map>
#include "ParamQueueMethodsOnly1.hpp"

typedef std::map<std::string, ParamQueue> QueueMap;

void exit(QueueMap& qs, std::string& sel) { exit(0); }
void new_queue(QueueMap& qs, std::string& sel)
{
  std::cout << "Input ParamQueue name: ";
  std::string name;
  std::cin.get();
  std::getline(std::cin, name);
  std::cout << "Do you want to input params now?(0_/1) > ";
  char ch;
  std::cin >> ch;
  std::vector<QueueElem> params{};
  while (ch == '1')
  {
    std::cout << "Input QueueElem (format: <number> <string>): ";
    params.push_back({});
    params.back().input();
    std::cout << "Do you want to continue?(0_/1) > ";
    std::cin >> ch;
  }
  qs[name] = ParamQueue(params);
  sel      = name;
  std::cout << "Successfully created!";
}

void remove_queue(QueueMap& qs, std::string& sel)
{
  std::cout << "Input ParamQueue name: ";
  std::string name;
  std::cin.get();
  std::getline(std::cin, name);
  qs.erase(name);
  std::cout << "Successfully removed!";
}

void print_queue(QueueMap& qs, std::string& sel)
{
  qs[sel].output(std::cout << "Selected ParamQueue: \n");

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
  std::cout << "Input ParamQueue name: ";
  std::string name;
  std::cin.get();
  std::getline(std::cin, name);
  if (qs.find(name) == qs.end())
  {
    std::cout << "ParamQueue not found!";
    return;
  }
  sel = name;
  std::cout << "ParamQueue '" << sel << "' selected!";
}

void add_params(QueueMap& qs, std::string& sel)
{
  char ch = '1';
  while (ch == '1')
  {
    std::cout << "Input QueueElem (format: <number> <string>): ";
    try
    {
      qs[sel].input();
    }
    catch (std::runtime_error& e)
    {
      std::cout << e.what() << std::endl;
      return;
    }
    std::cout << "Do you want to continue?(0_/1) > ";
    std::cin >> ch;
  }
}

void pop_params(QueueMap& qs, std::string& sel)
{
  char ch = '1';
  while (ch == '1')
  {
    QueueElem a;
    try
    {
      qs[sel].pop(a);
      a.output(std::cout << "Popped: ") << "\nDo you want to continue?(0_/1) > ";
    }
    catch (std::runtime_error& e)
    {
      std::cout << e.what() << std::endl;
      return;
    }
    std::cin >> ch;
  }
}

void check_stat(QueueMap& qs, std::string& sel) { std::cout << "ParamQueue status: " << qs[sel].check_state(); }

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
  queues["numbers"]    = ParamQueue({{1, "one"}, {2, "two"}, {3, "three"}});

  while (1)
  {
    std::cout << "Ask... \n\
    [0]Exit\n\
    [1]New ParamQueue\n\
    [2]Remove ParamQueue\n\
    [3]List queues\n\
    [4]Select ParamQueue\n\
    [5]Print ParamQueue\n\
    [6]Add to ParamQueue\n\
    [7]Pop from ParamQueue\n\
    [8]Check ParamQueue status\n"
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