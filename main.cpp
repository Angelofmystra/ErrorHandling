#include <iostream>
#include <string>
class Status {
private:
  bool ok_;
  std::string err_;
  bool is_ignored;
  unsigned err_code;
  std::string ret;
public:
  Status():
    ok_(true),
    err_(""),
    is_ignored(false),
    err_code(0),
    ret("OK!")
    {}
  Status(std::string& err, unsigned err_n):
    ok_(false),
    err_(err),
    is_ignored(false),
    err_code(err_n)
    {ret+="FAIL!";ret+=" Error Code: ";ret+=err_code;
    ret+="  Explanation: ";ret+=err_;} // DRY
  Status(std::string&& err, unsigned err_n):
    ok_(false),
    err_(err),
    is_ignored(false),
    err_code(err_n)
    {ret+="FAIL!";ret+=" Error Code: ";ret+=err_code;
    ret+="  Explanation: ";ret+=err_;} // DRY
  std::string error_message() const { return err_;}
  bool ok() const { return ok_;}
  std::string toString(){return ret;}
  void ignore_error(){is_ignored = true;} // ignoring an error is explicit
  //void is_ok(){ok_ = true;} // might remove this, to have better invariants
  //void is_not_ok(){ok_ = false;} // might remove this, to have better invariants
};

int main()
{
  Status status1;
  Status status2{"Failed to connect",1};
  std::cout << status1.toString() << std::endl;
  std::cout << status2.toString() << std::endl;
  status2.ignore_error();
  if(status1.ok()){ }
  if(not status2.ok()){std::cout << "Ok checker works" << std::endl; }
  return 0;
}
