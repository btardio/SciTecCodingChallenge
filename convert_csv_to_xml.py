import csv
import math
import pyproj
# example
#<doc>
#  <field name="id">0</field>
#  <field name="time">1234</field>
#  <field name="velocity">796.35</field>
#  <field name="xyzECEF">1,2,3</field>
#  <field name="xyzLLA">4,5,6</field>
#</doc>
#
#

def gps_to_ecef_pyproj(lat, lon, alt):


    ecef = pyproj.Proj(proj='geocent', ellps='WGS84', datum='WGS84')
    lla = pyproj.Proj(proj='latlong', ellps='WGS84', datum='WGS84')

    x, y, z = pyproj.transform(lla, ecef, lon, lat, alt, radians=False)

    return x, y, z

with open('SciTec_code_problem_data.csv') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    
    idx = 0

    print("<add>")

    for row in reader:
    
        s = ""
       


        try:
            
            lat,lon,alt = gps_to_ecef_pyproj(row[1], row[2], row[3])

            s += "<doc>\n"
            s += '  <field name="id">%s</field>\n' % idx
            s += '  <field name="time">%s</field>\n' % row[0].split(".")[0]
            s += '  <field name="velocity">0</field>\n'
            s += '  <field name="xyzECEF">%s,%s,%s</field>\n' % (lat,lon,alt)
            s += '  <field name="xyzLLA">%s,%s,%s</field>\n' % (row[1], row[2], row[3])
            s += "</doc>\n"
            idx += 1

            print(s)
        except IndexError as e:
            pass

    print("</add>")


