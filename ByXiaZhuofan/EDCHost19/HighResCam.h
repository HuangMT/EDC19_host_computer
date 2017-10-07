#pragma once

#include "stdafx.h"

struct ProcConfig
{
	int ball_hue_lb;
	int ball_hue_ub;

	int car1_hue_lb;
	int car1_hue_ub;

	int car2_hue_lb;
	int car2_hue_ub;

	int s_lb;
	int v_lb;
	int area_lb;
};

class ImgProc
{
public:
	CameraInfo GetLocation();

	//���� opencv ���ɻ��������������ʱ�ı����
	void InitCv();

	//��֤�����޸� mat
	void Locate(cv::Mat& mat);

	// ��λ�������
	ProcConfig config;
private:
	std::vector<cv::Point2f> ball_centers, car1_centers, car2_centers;
	//src : ��ֵ��ͼ��
	static std::vector<cv::Point2f> GetCenter(cv::Mat src, const ProcConfig & cfg);

	cv::Mat src, hsv;

	// 8UC1, hsv �� h ����
	cv::Mat hue;

	// ��ֵ��ͼ��s >= s_lb && h >= h_lb
	cv::Mat mask;

	// ��ֵ��ͼ��
	cv::Mat car1, car2, ball;

	// ��ɫͼ�񣬽� car1 car2 ball ����һ�𣬷�����ԣ��ֱ�ΪBGRͨ����
	cv::Mat merged;

	cv::Mat dst;
};

class HighResCam : public QAbstractVideoSurface
{
	Q_OBJECT

private:
	ImgProc locateMachine;
public:

	HighResCam(QObject *parent = nullptr);

	~HighResCam();

	QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const override;

	bool present(const QVideoFrame &frame) override;

signals:
	void ImageArrived(CameraInfo, QPixmap);
};
