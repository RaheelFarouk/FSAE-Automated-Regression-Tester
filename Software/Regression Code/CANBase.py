import can 
import time

class CANInterface:
    def __init__(self):
        # create a bus instance using 'with' statement,
        # this will cause bus.shutdown() to be called on the block exit;
        # many other interfaces are supported as well (see documentation)
        self.bus = can.interface.Bus(interface='pcan',
                    channel='PCAN_USBBUS2',
                    bitrate = 1000000,
                    receive_own_messages=True)
        # with can.Bus(interface='pcan',
        #             channel='PCAN_USBBUS2',
        #             bitrate = 1000000,
        #             receive_own_messages=True) as self.bus:

            # # send a message
            # self.message = can.Message(arbitration_id=123, is_extended_id=True,
            #                         data=[0x11, 0x22, 0x33])
            # self.bus.send(self.message, timeout=0.2)

            # # iterate over received messages
            # for msg in bus:
            #     print(f"{msg.arbitration_id:X}: {msg.data}")
            #     #    time.sleep(1)

            # # or use an asynchronous notifier
            # notifier = can.Notifier(self.bus, [can.Logger("recorded.log"), can.Printer()])
    
    def __del__(self):
        self.bus.shutdown()

    def send_can_message(self, can_id, is_extended, data):
        # send a message
        self.message = can.Message(arbitration_id=123, is_extended_id=True,
                                data=[0x11, 0x22, 0x33])
        self.bus.send(self.message, timeout=0.2)

    # def get_can_message():
    #     self.bus.
    def receive_can_message(self, timeout=None):
        return self.bus.recv(timeout=timeout)



canInterface = CANInterface()
canInterface.send_can_message(can_id=0xA11, data=[0x11, 0x22, 0x33], is_extended=False)

while True:
    print(canInterface.receive_can_message())