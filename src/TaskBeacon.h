#ifndef TASK_BEACON_H_
#define TASK_BEACON_H_

#include <OneButton.h>
#include <TinyGPS++.h>

#include <APRSMessage.h>
#include <TaskMQTT.h>
#include <TaskManager.h>

class BeaconTask : public Task {
public:
  BeaconTask(TaskQueue<std::shared_ptr<APRSMessage>> &toModem, TaskQueue<std::shared_ptr<APRSMessage>> &toAprsIs);
  virtual ~BeaconTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

  static String create_lat_aprs(double lat);
  static String create_long_aprs(double lng);

private:
  TaskQueue<std::shared_ptr<APRSMessage>> &_toModem;
  TaskQueue<std::shared_ptr<APRSMessage>> &_toAprsIs;

  std::shared_ptr<APRSMessage> _beaconMsg;
  Timer                        _beacon_timer;

  HardwareSerial _ss;
  TinyGPSPlus    _gps;
  bool           _useGps;

  OneButton   _userButton;
  static bool _send_update;

  bool        sendBeacon(System &system);
  static void pushButton();
};

#endif
