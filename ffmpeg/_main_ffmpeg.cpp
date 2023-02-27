#include <iostream>
using namespace std;

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
}

int main2()
{
	printf("%s", avcodec_configuration());
	system("pause");
	return 0;
}



//ʵ�ָ��ַ�װ��ʽת��
#include<iostream>
#include<libavutil/timestamp.h>
#include<libavformat/avformat.h>

int main(int argc, char* argv[])
{
	//�����ʽ
	const AVOutputFormat* ofmt = NULL;
	//���������ý������
	AVFormatContext* ifmt_ctx = NULL, * ofmt_ctx = NULL;
	AVPacket* pkt = NULL;
	//��������ļ����֡�
	const char* in_filename, * out_filename;
	in_filename = "D:/data/ws/cpp/ConsoleApplication/out/in.mkv";
	out_filename = "D:/data/ws/cpp/ConsoleApplication/out/out.mkv";
	int ret = -1;
	//���ڴ洢��������������
	int* stream_mapping = NULL;
	int stream_index = 0;
	int frame_index = 0;

	//if (argc < 2)
	//{
	//	std::cout << "����������ļ�������ļ���������ִ�иó���" << std::endl;
	//	return -1;
	//}
	//in_filename = argv[1];
	//out_filename = argv[2];

	//��Դ�ļ���
	ret = avformat_open_input(&ifmt_ctx, in_filename, 0, 0);
	if (ret < 0)
	{
		std::cout << "could not open the filename :" << in_filename << std::endl;
		goto end;
	}
	else {
		std::cout << "open the filename :" << in_filename << " success" << std::endl;
	}
	ret = avformat_find_stream_info(ifmt_ctx, 0);
	if (ret < 0) {
		std::cout << "avformat_find_stream_info filed!" << std::endl;
		goto end;
	}
	//��ӡ��ϸ��Ϣ��
	//av_dump_format(ifmt_ctx, 0, in_filename, 0);

	stream_mapping = new int[ifmt_ctx->nb_streams];
	//Ϊ�����media handle����ռ�
	avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_filename);
	if (!ofmt_ctx) {
		std::cout << "Could not create output context!" << std::endl;
		avformat_close_input(&ifmt_ctx);
		goto end;
	}
	ofmt = ofmt_ctx->oformat;
	for (int i = 0; i < ifmt_ctx->nb_streams; i++)  //nb_streams==2;
	{
		//���������������������Create output AVStream according to input AVStream��
		AVStream* in_stream = ifmt_ctx->streams[i];
		AVCodecParameters* in_codecpar = in_stream->codecpar;
		AVStream* out_stream = NULL;
		if (in_codecpar->codec_type != AVMEDIA_TYPE_AUDIO &&
			in_codecpar->codec_type != AVMEDIA_TYPE_VIDEO)
		{
			//���ｫ��������ֵ��Ϊ-1,���������֡ʱ������
			stream_mapping[i] = -1;
			continue;
		}
		//��Ҫ������ý�������������洢��
		stream_mapping[i] = stream_index;
		stream_index++;
		//�½�һ��ý����
		out_stream = avformat_new_stream(ofmt_ctx, NULL);
		if (!out_stream)
		{
			std::cout << "avformat_new_stream failed" << std::endl;
			avformat_close_input(&ifmt_ctx);
			goto end;
		}
		//��������
		ret = avcodec_parameters_copy(out_stream->codecpar, in_codecpar);
		if (ret < 0)
		{
			std::cout << "avcodec_parameters_copy filed!" << std::endl;
			goto end;
		}
		out_stream->codecpar->codec_tag = 0;
	}
	//���һ�¸�ʽ------------------
	av_dump_format(ofmt_ctx, 0, out_filename, 1);
	//������ļ���Open output file��
	if (!(ofmt->flags & AVFMT_NOFILE)) {
		ret = avio_open(&ofmt_ctx->pb, out_filename, AVIO_FLAG_WRITE);
		if (ret < 0) {
			std::cout << "could not open the outputfile:" << out_filename << std::endl;
			goto end;
		}
	}
	//д�ļ�ͷ��Write file header��
	ret = avformat_write_header(ofmt_ctx, NULL);
	if (ret < 0) {
		std::cout << "avformat_write_header failed!" << std::endl;
		goto end;
	}
	pkt = av_packet_alloc();
	while (1)
	{
		AVStream* in_stream = NULL;
		AVStream* out_stream = NULL;
		//��ȡpkt
		ret = av_read_frame(ifmt_ctx, pkt);
		if (ret < 0)
		{
			std::cout << "=== read the end of the file��" << std::endl;
			break;
		}
		in_stream = ifmt_ctx->streams[pkt->stream_index];
		if (stream_mapping[pkt->stream_index] < 0) {
			av_packet_unref(pkt);
			continue;
		}
		pkt->stream_index = stream_mapping[pkt->stream_index];
		/*
		out_stream = ofmt_ctx->streams[pkt->stream_index];
		//copy packet
		//ʱ�����ת��
		//ת��PTS/DTS��Convert PTS/DTS��
		pkt->pts = av_rescale_q_rnd(pkt->pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt->dts = av_rescale_q_rnd(pkt->dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt->duration = av_rescale_q(pkt->duration, in_stream->time_base, out_stream->time_base);
		//std::cout << pkt->pts << "=" << pkt->dts << "=" << pkt->duration << std::endl;
		//std::cout << pkt->stream_index << "=" << pkt->flags << "=" << pkt->size<< std::endl;
		pkt->pos = -1;
		*/

		//д�루Write��
		ret = av_interleaved_write_frame(ofmt_ctx, pkt);
		if (ret < 0) {
			std::cout << "av_interleaved_write_frame failed!" << std::endl;
			break;
		}
		frame_index++;
		if (frame_index % 1000 == 0)
		{
			std::cout << "Write frames to output file:" << frame_index << std::endl;
		}
		//�ǵ����ü�����1,����������ڴ�й©��
		av_packet_unref(pkt);
	}
	//д�ļ�β��Write file trailer��

end:
	delete[] stream_mapping;
	avformat_close_input(&ifmt_ctx);
	av_write_trailer(ofmt_ctx);
	av_packet_free(&pkt);
	avformat_close_input(&ifmt_ctx);
	if (ofmt_ctx && !(ofmt->flags & AVFMT_NOFILE))
		avio_close(ofmt_ctx->pb);
	avformat_free_context(ofmt_ctx);
	if (ret < 0 && ret != AVERROR_EOF) {
		printf("Error occurred.\n");
		return -1;
	}
	system("pause");
	return 0;
}