#include "BH1750FVI.h"


bh1750fvi::bh1750fvi(uint8_t addr, uint16_t acq_mode)
  : i2c_peripheral(address), mode(acq_mode)
{
  change_mode(mode);
}

bh1750fvi::~bh1750fvi()
{
  send_command(RESET);
  send_command(POWER_OFF);
}

uint16_t bh1750fvi::get_data()
{
  switch(mode)
  {
    // For continuous mode, we just need to read the latest value
    // from the device
    case CONTINUOUS_H_MODE:
    case CONTINUOUS_H_MODE2:
    case CONTINUOUS_L_MODE:
    {
      // TODO
      break;
    }

    // For one-shot mode, got to turn device on and request data
    case ONE_TIME_H_MODE:
    case ONE_TIME_H_MODE2:
    case ONE_TIME_L_MODE:
    {
      send_command(POWER_ON);
      send_command(mode);
      // TODO: wait...
      // TODO: read in I2C data
      break;
    }

    default:
    {
      // TODO: throw
      break;
    }
  }
}

void bh1750fvi::change_mode(uint16_t acq_mode)
{
  mode = acq_mode;

  send_command(POWER_OFF);
  switch(mode)
  {
    case CONTINUOUS_H_MODE:
    case CONTINUOUS_H_MODE2:
    case CONTINUOUS_L_MODE:
    {
      send_command(POWER_ON);
      // TODO: send command to start continuous mode
      break;
    }

    case ONE_TIME_H_MODE:
    case ONE_TIME_H_MODE2:
    case ONE_TIME_L_MODE:
    {
      break;
    }

    default:
    {
      // TODO: throw
      break;
    }
  }
}

void bh1750fvi::send_command()
{
  // FIXME: is this necessary if we inherit from i2c_peripheral ?
  //        Remember, need to suffix address with '0' for write commands
}
