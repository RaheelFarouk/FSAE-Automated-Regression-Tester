import math

import cantools.database 
from CANBase import CANInterface

import cantools
import os
dbc_directory = os.path.join(os.getcwd(), 'Software\DBC Tools\output.dbc')
dbc_file = dbc_directory #'..\DBC Tools\output.dbc'
db = cantools.database.load_file(dbc_file)

message = db.get_message_by_name('HARDINJ_command')

data = message.encode({
    'HARDINJ_mux': 0,
    'HARDINJ_output1Control': 127,
    'HARDINJ_output2Control': 200,
    'HARDINJ_output3Control': 200,
    'HARDINJ_output4Control': 200,
    'HARDINJ_output5Control': 200,
    'HARDINJ_output6Control': 200,

})


def startCAN():
    can_interface = CANInterface()
    can_interface.send_can_message(can_id=0x001, data=data, is_extended=False)
    can_interface.__del__()
    print("test")
    assert(True==True)

def test_sqrt():
    num = 25
    assert math.sqrt(25) == 5

def test_can():
    print(data)
    startCAN()
