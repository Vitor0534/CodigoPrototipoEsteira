
class Motor{
  int maximo_RPM;
  
  public:
  Motor(int maximo_RPM){
    this->maximo_RPM = maximo_RPM;
  }
  int get_maximo_RPM(){
    return maximo_RPM;
  }
};
