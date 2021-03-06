#include <iostream>
#include <string>
/*
 In order to make this implementation work, the compiler needs to be rigged so it will fail to compile if an unignored error occurs. I am not yet sure as to how to do this.
*/
class Status {
private:
  bool ok_;
  std::string err_;
  bool is_ignored;
  std::string ignored_reason_;
  unsigned err_code;
  std::string ret;
public:
  Status():
    ok_(true),
    err_(""),
    is_ignored(false),
    ignored_reason_(""),
    err_code(0),
    ret("OK!")
    {}
  Status(std::string& err, unsigned err_n):
    ok_(false),
    err_(err),
    is_ignored(false),
    ignored_reason_(""),
    err_code(err_n)
    {ret+="FAIL!";ret+=" Error Code: ";ret+=err_code;
    ret+="  Explanation: ";ret+=err_;} // DRY
  Status(std::string&& err, unsigned err_n):
    ok_(false),
    err_(err),
    is_ignored(false),
    ignored_reason_(""),
    err_code(err_n)
    {ret+="FAIL!";ret+=" Error Code: ";ret+=err_code;
    ret+="  Explanation: ";ret+=err_;} // DRY
  std::string error_message() const { return err_;}
  bool ok() const { return ok_;}
  std::string toString(){return ret;}
  void ignore_error(std::string reason){is_ignored = true;ignored_reason_=reason;} // ignoring an error is explicit
  //void is_ok(){ok_ = true;} // might remove this, to have better invariants
  //void is_not_ok(){ok_ = false;} // might remove this, to have better invariants
};

int main()
{
  Status status1;
  Status status2{"Failed to connect",1};
  std::cout << status1.toString() << std::endl;
  std::cout << status2.toString() << std::endl;
  status2.ignore_error("Some legitimate reason");
  if(status1.ok()){ }
  if(not status2.ok()){std::cout << "Ok checker works" << std::endl; }
  return 0;
}
