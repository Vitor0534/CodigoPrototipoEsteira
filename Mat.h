
class Mat{
  int maximoRPM;
  
  public:
  Mat(int maximo_RPM){
    this->maximoRPM = maximo_RPM;
  }
  int getMaxRPM(){
    return maximoRPM;
  }

  void setMaxRPM(int maxRPM){
    this->maximoRPM = maxRPM;
  }
};
