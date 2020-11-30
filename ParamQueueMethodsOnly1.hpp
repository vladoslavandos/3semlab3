#include <cstring>
#include <iostream>
#include <string>
#include <vector>

struct QueueElem
{
  static constexpr size_t __n = 3;
  int num;
  char str[__n];
  // Construct a new Queue Elem object
//  _num Number data
// _str String data of length __n
   
  QueueElem(int const& _num = 0, char const _str[__n] = "") : num(_num)
  {
    size_t strl = std::strlen(_str);
    for (size_t i = 0; i < __n; i++)
      if (i < strl)
        str[i] = _str[i];
      else
        str[i] = '\0';
  }
  
  std::istream& input(std::istream& stream = std::cin) { return (stream >> num).get(*str).get(str, __n); }
  
  std::ostream& output(std::ostream& stream = std::cout) { return stream << "(" << num << ", " << str << ")"; }
};

//Queue filling state enum
 
enum QueueState
{ 
  empt, part, full
};
// Parameter Queue
struct ParamQueue
{
  static constexpr size_t __n = 3;

private:
  size_t front, back;
  QueueElem queue[__n];

public:
  // Construct a new ParamQueue object from std::vector of elements
  ParamQueue(std::vector<QueueElem> _q = {}) : front(0), back(0)
  {
    for (size_t i = 0; i < _q.size(); i++)
      push(_q[i]);
  }
  //Input one element from stream
  std::istream& input(std::istream& stream = std::cin)
  {
    if ((back >= __n) != (front >= __n) && back % __n == front % __n)
      throw std::runtime_error("Queue overflow");
    queue[(back++) % __n].input(stream);
    back %= 2 * __n;
    return stream;
  }
  //Output to stream
  std::ostream& output(std::ostream& stream = std::cout)
  {
    for (size_t i = front; i != back; (++i) %= 2 * __n)
    {
      queue[i % __n].output(stream);
    }
    return stream;
  }
  //Take first element from queue
  //elem Reference to an object to fill
  
  ParamQueue& pop(QueueElem& elem)
  {
    if ((back >= __n) == (front >= __n) && back % __n == front % __n)
      throw std::runtime_error("Queue is empty");
    elem = queue[(front++) % __n];
    front %= 2 * __n;
    return *this;
  }
  //Add to queue
  QueueElem& push(QueueElem const& elem)
  {
    if ((back >= __n) != (front >= __n) && back % __n == front % __n)
      throw std::runtime_error("Queue overflow");
    queue[(back++) % __n] = elem;
    back %= 2 * __n;
    return queue[(back + __n - 1) % __n];
  }
  
  QueueState check_state() const
  {
    if (back % __n == front % __n)
    {
      if ((back >= __n) == (front >= __n))
        return QueueState::empt;
      else
        return QueueState::full;
    }
    else
      return QueueState::part;
  }
};

std::ostream& operator<<(std::ostream& stream, QueueState state)
{
  return stream << (state != QueueState::empt ? (state == QueueState::part ? "Partially full" : "Full") : "Empty");
}