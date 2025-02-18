#include <nana/gui.hpp>
#include <nana/gui/widgets/listbox.hpp>

#include <vector>

namespace quantity
{
  enum class Unit
  {
    Mass,
    Volume,
    Length,
    Time,
    Temperature,
    
    Count
  };

  struct Exponent
  {
  protected:
    Unit _unit;
    int _magnitude;

  public:
    Exponent(Unit unit, int magnitude) : _unit(unit), _magnitude(magnitude) { }
    Exponent(Unit unit) : _unit(unit), _magnitude(1) { }
  };

  struct Value
  {
    double value;

    Value(uint64_t value) : value(value) { }
    Value() : value(0.0) { }
  };

  class Quantity
  {
  protected:
    std::vector<Exponent> _exponents;
    Value _value;

  public:
    Quantity() { }
    Quantity(Value value) : _value(value) { }
    Quantity(Value value, Exponent exponent) : _value(value), _exponents({ exponent }) { }

  };

  struct Quantities
  {
    static Quantity count(uint64_t amount) { return Quantity(Value(amount), Exponent(Unit::Count)); }
  };


}

int main()
{
  /* create a nana window and add a listbox to it */
  nana::form fm;
  nana::listbox lb(fm, nana::rectangle(0, 0, 640, 480));

  lb.append_header("Description");
  lb.append_header("Value");
  lb.append_header("Unit");

  auto category = lb.at(0);
  category.append({ "WBC", "6.57", "10³/mm³"});

  fm.show();

  nana::exec();
} 