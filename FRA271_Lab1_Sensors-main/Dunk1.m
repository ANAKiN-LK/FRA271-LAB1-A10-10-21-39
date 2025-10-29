% โหลด dataset จาก workspace
adc_dataset = data;              % ตัวแปรหลักชื่อ data
adc_ts = adc_dataset{1}.Values;  % ดึง timeseries ออกมา

% แปลงข้อมูลเป็น double และ flatten มิติ 1x1xN
t = adc_ts.Time(:);
y = double(squeeze(adc_ts.Data));

% สร้าง timeseries ใหม่ที่ Simulink ใช้ได้
adc_clean = timeseries(y, t, 'Name', 'ADC_Clean');

% plot ตรวจสอบ
figure;
plot(adc_clean.Time, adc_clean.Data, 'LineWidth', 1.5);
xlabel('Time (s)');
ylabel('ADC Value');
title('ADC Cleaned from Dataset');
grid on;