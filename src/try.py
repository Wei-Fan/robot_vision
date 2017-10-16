#!/usr/bin/env python
import httplib, urllib, base64, json, os, sys
import random
import rospy
from std_msgs.msg import String

if __name__ == '__main__':
    rospy.init_node('pytry', anonymous=True)
    
    image_path="/home/wade/catkin_ws/src/robot_vision/src/07.jpg"#sys.argv[1]

    headers = {
        # Request headers
        'Content-Type': 'application/octet-stream',
        'Ocp-Apim-Subscription-Key': 'a81e36ccb4894999ae3cd89750e4a07d',
    }

    params = urllib.urlencode({})

    try:
        conn = httplib.HTTPSConnection('westus.api.cognitive.microsoft.com')
        conn.request("POST", "/emotion/v1.0/recognize?%s" % params, open(image_path, "rb").read(), headers)
        response = conn.getresponse()
        data = response.read()
        res=json.loads(data)
        print res
        number=random.randint(1,10)
        if (res[0]["scores"]["happiness"]>0.5):
            #os.system("play happiness/%d.mp3"%(number))
            print 'OA: You are happy!'
            os.system("play /home/wade/catkin_ws/src/robot_vision/src/happiness/%d.mp3"%(number))
        elif (res[0]["scores"]["anger"]>0.5):
        	print 'OA: Please do not be mad!'
        	os.system("play /home/wade/catkin_ws/src/robot_vision/src/anger/1.mp3")
            #os.system("play anger/%d.mp3"%(number))
        elif (res[0]["scores"]["contempt"]>0.5):
            os.system("play contempt/%d.mp3"%(number))
        elif (res[0]["scores"]["disgust"]>0.5):
            os.system("play disgust/%d.mp3"%(number))
        elif (res[0]["scores"]["fear"]>0.5):
            os.system("play fear/%d.mp3"%(number))
        elif (res[0]["scores"]["neutral"]>0.5):
            os.system("play neutral/%d.mp3"%(number))
        elif (res[0]["scores"]["sadness"]>0.5):
            os.system("play sadness/%d.mp3"%(number))
        elif (res[0]["scores"]["surprise"]>0.5):
        	print 'OA: What makes you so surprise?'
        	os.system("play /home/wade/catkin_ws/src/robot_vision/src/surprise/1.mp3")
            #os.system("play surprise/%d.mp3"%(number))
        else:
            os.system("play zero/%d.mp3"%(number))
        conn.close()
    except Exception as e:
        print("[Errno {0}] {1}".format(e.errno, e.strerror))
