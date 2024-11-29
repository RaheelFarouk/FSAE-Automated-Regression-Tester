import math
import time

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


def start_CAN():
    can_interface = CANInterface()
    can_interface.send_can_message(can_id=message.frame_id, data=data, is_extended=False)
    can_interface.__del__()
    print("test")
    assert(True==True)

def test_sqrt():
    num = 25
    assert math.sqrt(25) == 5

def test_can():
    print(data)
    start_CAN()
    can_interface = CANInterface()
    can_interface.send_and_update_can_message(can_id=0x001, data=data, is_extended=False)
    time.sleep(10)
    can_interface.__del__()
    assert(True==True)

def test_strain_gauge_amp():
    dbc_directory = os.path.join(os.getcwd(), 'Software\DBC Tools\Strain Gauge DBC.dbc')
    dbc_file = dbc_directory #'..\DBC Tools\output.dbc'
    db = cantools.database.load_file(dbc_file)

    message = db.get_message_by_name('SGAMP1_data1000Hz')

    data = message.encode({
        'SGAMP1_outputVoltage': -32768,
        'SGAMP1_ambientTemp': 100,
    })
    start_CAN()