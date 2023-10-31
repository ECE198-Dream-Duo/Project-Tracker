#define maxSpeed 5.0
#define maxAcceleration 1.0

struct AbstractPID {
public:
  AbstractPID(float AKp, float AKi, float AKd) : Kp(AKp), Ki(AKi), Kd(AKd), MS(maxSpeed), MA(maxAcceleration) {}

protected:
  /*
  * 
  */
  void CalculateError(double Position, double Setpoint);
  /*
  * Calculates P, I, D and then puts our Error through it to find our new Power Required, Which will be bottlenecked by our max Speed and max Acceleration
  * P(t) = Kp * e(t) | Proportional aspect
  * I(t) = Ki * ∫ e(t) dt | Integral aspect
  * D(t) = Kd * de(t)/dt | Derivative aspect
  * u(t) = P(t) + I(t) + D(t) -> we want this value
  */
  void CalculatePower(double Position, double Setpoint, double CurrTime);
private:
  float Kp = 0; // Can be calculated through trial and error
  float Ki = 0;
  float Kd = 0;
  float MS;
  float MA;
  double lasttime = 0.0;
}