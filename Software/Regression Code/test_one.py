import math 
from CANBase import CANInterface

def startCAN():
    can_interface = CANInterface()
    can_interface.send_can_message(can_id=0xA11, data=[0x11, 0x22, 0x33], is_extended=False)
    can_interface.__del__()
    print("test")
    assert(True==True)

def test_sqrt():
    num = 25
    assert math.sqrt(25) == 5

def test_can():
    startCAN()
