
import time
import sys

import cantools
import os

# Get the parent directory path
parent_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
# Add the parent directory to sys.path
sys.path.insert(0, parent_dir)

from CANBase import CANInterface

dbc_directory = os.path.join(os.getcwd(), 'Software\DBC Tools\output.dbc')
dbc_file = dbc_directory #'..\DBC Tools\output.dbc'
db = cantools.database.load_file(dbc_file)

def test_add_message_100Hz():
    from data.message_data import MessageData
    message = MessageData(message=db.get_message_by_name('HARDINJ_command'), 
                          data={
                                'HARDINJ_mux': 0,
                                'HARDINJ_output1Control': 127,
                                'HARDINJ_output2Control': 200,
                                'HARDINJ_output3Control': 200,
                                'HARDINJ_output4Control': 200,
                                'HARDINJ_output5Control': 200,
                                'HARDINJ_output6Control': 200,
                                }
    )

    message2 = MessageData(message=db.get_message_by_name('HARDINJ_command'), 
                          data={
                                'HARDINJ_mux': 0,
                                'HARDINJ_output1Control': 0,
                                'HARDINJ_output2Control': 10,
                                'HARDINJ_output3Control': 10,
                                'HARDINJ_output4Control': 10,
                                'HARDINJ_output5Control': 10,
                                'HARDINJ_output6Control': 10,
                                }
    )


    can_interface = CANInterface()
    can_interface.start_send_and_update_100Hz()
    # can_interface.send_and_update_can_message(can_id=message.frame_id, data=data, is_extended=False)
    # can_interface.send_and_update_can_message_100Hz(can_frame=message)
    can_interface.add_message_100Hz(message)
    time.sleep(2)
    can_interface.add_message_100Hz(message2)
    time.sleep(2)

    message2.data = {
                    'HARDINJ_mux': 0,
                    'HARDINJ_output1Control': 127,
                    'HARDINJ_output2Control': 200,
                    'HARDINJ_output3Control': 200,
                    'HARDINJ_output4Control': 200,
                    'HARDINJ_output5Control': 200,
                    'HARDINJ_output6Control': 200,
                    }

    can_interface.add_message_100Hz(message2)
    time.sleep(2)
    can_interface.stop_send_and_update_100hz()



test_add_message_100Hz()

time.sleep(10)
# can_interface.__del__()