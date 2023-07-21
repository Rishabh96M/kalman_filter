import matplotlib.pyplot as plt

time1 = []
gt_pos1 = []
noise_pos1 = []
est_pos1 = []
error_pos1 = []

file_path  = "results/output1.txt"

with open(file_path, 'r') as file:
    for line in file:
        values = line.split(",")
        time1.append(float(values[0]))
        gt_pos1.append(float(values[1]))
        noise_pos1.append(float(values[2]))
        est_pos1.append(float(values[3]))
        error_pos1.append(float(values[4]))



time2 = []
gt_pos2 = []
est_pos2 = []
error_pos2 = []
cam_pos = []
cam_time = []
rad_pos = []
rad_time = []

file_path  = "results/output2.txt"
with open(file_path, 'r') as file:
    for line in file:
        values = line.split(",")
        time2.append(float(values[0]))
        gt_pos2.append(float(values[1]))
        est_pos2.append(float(values[2]))
        error_pos2.append(float(values[3]))

file_path  = "data/cam_data2.txt"
with open(file_path, 'r') as file:
    for line in file:
        values = line.split(",")
        cam_time.append(float(values[0]))
        cam_pos.append(float(values[1]))

file_path  = "data/rad_data2.txt"
with open(file_path, 'r') as file:
    for line in file:
        values = line.split(",")
        rad_time.append(float(values[0]))
        rad_pos.append(float(values[1]))

plt.figure(1)
plt.plot(time1, gt_pos1, label='GT Pos')
plt.plot(time1, est_pos1, label='Est Pos')
plt.plot(time1, noise_pos1, label='noise Pos')

plt.xlabel('Time')
plt.ylabel('Position')
plt.title('Plotting Position vs Time')
plt.legend()


plt.figure(2)
plt.plot(time2, gt_pos2, label='GT Pos')
plt.plot(time2, est_pos2, label='Est Pos')
plt.plot(cam_time, cam_pos, '.', label='Cam Pos')
plt.plot(rad_time, rad_pos, '.', label='Rad Pos')

plt.xlabel('Time')
plt.ylabel('Position')
plt.title('Plotting Position vs Time')
plt.legend()

plt.show()
