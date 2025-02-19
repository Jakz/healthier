//#include <nana/gui.hpp>
//#include <nana/gui/widgets/listbox.hpp>

#include <vector>
#include <string>

namespace qty
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

    std::string caption() const;
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

    Quantity operator*(Unit unit) const { Quantity result = *this; result._exponents.push_back(Exponent(unit)); return result; }
    Quantity operator*(Exponent exponent) const { Quantity result = *this; result._exponents.push_back(exponent); return result; }

    std::string caption();
  };

  struct Quantities
  {
    static Quantity count(uint64_t amount) { return Quantity(Value(amount), Exponent(Unit::Count)); }

  };

  struct Units
  {
    static Exponent milliliter() { return Exponent(Unit::Volume, -3); }
  }

}

using namespace qty;

std::string Exponent::caption() const
{
  switch (_unit)
  {
    case Unit::Count: return "";
    case Unit::Volume:
    {
      switch (_magnitude)
      {
        case 1: return "L";
        case 2: return "mL";
        case 3: return "µL";
        case 4: return "nL";
        case 5: return "pL";
        case 6: return "fL";
        case 7: return "aL";
        case 8: return "zL";
        case 9: return "yL";
        default: return "";
      }
    }
  }

  return "";
}

std::string Quantity::caption()
{
 std::string caption = std::to_string(_value.value);
  for (auto& exponent : _exponents)
  {
    caption += " " + exponent.caption();
  }
  
  return caption;
}


#include <iostream>

int main()
{
  using namespace qty;
  Quantity wbc = Quantities::count(6570);
  Quantity wbcml = wbc * Units::milliliter();

  std::cout << wbcml.caption() << std::endl;
  /* create a nana window and add a listbox to it */
  /*nana::form fm;
  nana::listbox lb(fm, nana::rectangle(0, 0, 640, 480));

  lb.append_header("Description");
  lb.append_header("Value");
  lb.append_header("Unit");

  auto category = lb.at(0);
  category.append({ "WBC", "6.57", "10³/mm³"});

  fm.show();

  nana::exec();*/
} 