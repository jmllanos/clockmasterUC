#include <CGS.h>

//revisar si esta conectado!!##############################################################
//revisar si esta conectado!!##############################################################

void CGS::begin()
{
    IC.begin();
    DEBUG_CM_PRINTLN("begin done");
    string_reply = String("\"begin\":\"ok\"");
}

void CGS::mask_irq(char* data)
{
    StaticJsonBuffer<800> jsonBuffer;
    JsonObject& mask_irq = jsonBuffer.parseObject(data);
    uint8_t aux = IC.mask_irq((uint8_t)mask_irq["field"],
                                 (bool)mask_irq["mask"]);
    if (aux == 0){
        DEBUG_CM_PRINTLN("mask_irq done");
        string_reply = String("\"mask_irq\":\"ok\"");
    }
    else {
        DEBUG_CM_PRINT("mask_irq failed: ");
        DEBUG_CM_PRINTLN(aux);
        string_reply = String("\"mask_irq\":\"fail\"");
    }
}

void CGS::read_irq_sticky(char* data)
{
    StaticJsonBuffer<800> jsonBuffer;
    JsonObject& read_irq_sticky = jsonBuffer.parseObject(data);
    uint8_t aux = IC.read_irq_sticky((uint8_t)read_irq_sticky["field"]);
    if (aux == 0){
        DEBUG_CM_PRINTLN("read_irq_sticky done");
        string_reply = String("\"read_irq_sticky\":\"ok\"");
    }
    else {
        DEBUG_CM_PRINT("read_irq_sticky failed: ");
        DEBUG_CM_PRINTLN(aux);
        string_reply = String("\"read_irq_sticky\":\"fail\"");
    }
}

void CGS::get_status(char* data)
{
    StaticJsonBuffer<800> jsonBuffer;
    JsonObject& get_status = jsonBuffer.parseObject(data);
    uint8_t aux = IC.get_status((uint8_t)get_status["field"]);
    if (aux == 0){
        DEBUG_CM_PRINTLN("get_status done");
        string_reply = String("\"get_status\":\"ok\"");
    }
    else {
        DEBUG_CM_PRINT("get_status failed: ");
        DEBUG_CM_PRINTLN(aux);
        string_reply = String("\"get_status\":\"fail\"");
    }
}

void CGS::set_pll(char* data)
{
    StaticJsonBuffer<800> jsonBuffer;
    JsonObject& set_pll = jsonBuffer.parseObject(data);
    IC.set_pll((bool)set_pll["pll"],
               (bool)set_pll["ref"],
            (uint8_t)set_pll["multiplier"]);
    DEBUG_CM_PRINTLN("set_pll done");
    string_reply = String("\"set_pll\":\"ok\"");
}

void CGS::set_clk_frac(char* data)
{
    StaticJsonBuffer<800> jsonBuffer;
    JsonObject& set_clk_frac = jsonBuffer.parseObject(data);
    uint8_t aux = IC.set_clk_frac((uint8_t)set_clk_frac["clk"],
                                     (bool)set_clk_frac["pll"],
                                  (uint8_t)set_clk_frac["divider"]);
    if (aux == 0){
        DEBUG_CM_PRINTLN("set_clk_frac done");
        string_reply = String("\"set_clk_frac\":\"ok\"");
    }
    else {
        DEBUG_CM_PRINT("set_clk_frac failed: ");
        DEBUG_CM_PRINTLN(aux);
        string_reply = String("\"set_clk_frac\":\"fail\"");
    }
}

void CGS::clk_ena(char* data)
{
    StaticJsonBuffer<800> jsonBuffer;
    JsonObject& clk_ena = jsonBuffer.parseObject(data);
    IC.clk_ena((uint8_t)clk_ena["clk"],
                  (bool)clk_ena["condition"]);
    DEBUG_CM_PRINTLN("clk_ena done");
    string_reply = String("\"clk_ena\":\"ok\"");
}

String CGS::getReplyMessage()
{
    return string_reply;
}

//*****************************************************************************
// Checks i2c bus conexion.
//
// Dumb write to check for bus errors and return i2c error code. If used, this
// function would fit better before any attempt to write or read the IC.
//
// \return 0: success
// \return 1: data too long to fit in transmit buffer
// \return 2: received NACK on transmit of address
// \return 3: received NACK on transmit of data
// \return 4: other tx error 
// \return 5: rx error
//*****************************************************************************
uint8_t CGS::CheckBus()
{
  uint8_t aux1 = 0;
  uint8_t aux2 = 0;
  aux1 = IC.write_register(SI5351_REG_3_OUTPUT_ENABLE_CONTROL, 0x3F);
  aux2 = IC.read_register(SI5351_REG_3_OUTPUT_ENABLE_CONTROL);
  IC.write_register(SI5351_REG_3_OUTPUT_ENABLE_CONTROL, 0x00); // default reset value
  if (aux1 == 0)
  {
    if (aux2 != 0x3F) return 5;
    else return 0;
  }
  else return aux1;
}