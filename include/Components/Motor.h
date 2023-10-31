
struct Motor {
public:

protected:
  double VoltagetoSpeed(double Voltage);
  double SpeedtoVoltage(double Speed);
  void Brake();
  void SetSpeed(double Speed);
  void SetVoltage(double Voltage);
private:
  double CurrVoltage; // Found using experimentation
  double CurrSpeed;
  double CurrRPM;
};  