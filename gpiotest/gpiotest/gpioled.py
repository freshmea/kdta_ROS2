import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import RPi.GPIO as g
import time

g.setmode(g.BCM)
g.setup(21, g.OUT)


class Hbmove(Node):
    def __init__(self):
        super().__init__("minimal_publisher")  # type: ignore
        self.create_timer(1, self.hello_world_callback)
        self.pub = self.create_publisher(String, "hello", 10)
        self.count = 0
    def hello_world_callback(self):
        msg = String()
        msg.data = "Hello World! " + str(self.count)
        self.pub.publish(msg)
        self.count += 1
        if self.count%2 == 1:
            g.output(21, True)
        else:
            g.output(21, False)


def main():
    rclpy.init()
    node = Hbmove()
    try:
        rclpy.spin(node)
    except:
        g.cleanup(21)
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
