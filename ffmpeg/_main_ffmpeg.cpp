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



//实现各种封装格式转换
#include<iostream>
#include<libavutil/timestamp.h>
#include<libavformat/avformat.h>

int main(int argc, char* argv[])
{
	//输出格式
	const AVOutputFormat* ofmt = NULL;
	//输入于输出媒体句柄。
	AVFormatContext* ifmt_ctx = NULL, * ofmt_ctx = NULL;
	AVPacket* pkt = NULL;
	//输入输出文件名字。
	const char* in_filename, * out_filename;
	in_filename = "D:/data/ws/cpp/ConsoleApplication/out/in.mkv";
	out_filename = "D:/data/ws/cpp/ConsoleApplication/out/out.mkv";
	int ret = -1;
	//用于存储输入流的索引。
	int* stream_mapping = NULL;
	int stream_index = 0;
	int frame_index = 0;

	//if (argc < 2)
	//{
	//	std::cout << "请键入输入文件和输出文件参数重新执行该程序！" << std::endl;
	//	return -1;
	//}
	//in_filename = argv[1];
	//out_filename = argv[2];

	//打开源文件。
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
	//打印详细信息。
	//av_dump_format(ifmt_ctx, 0, in_filename, 0);

	stream_mapping = new int[ifmt_ctx->nb_streams];
	//为输出的media handle申请空间
	avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_filename);
	if (!ofmt_ctx) {
		std::cout << "Could not create output context!" << std::endl;
		avformat_close_input(&ifmt_ctx);
		goto end;
	}
	ofmt = ofmt_ctx->oformat;
	for (int i = 0; i < ifmt_ctx->nb_streams; i++)  //nb_streams==2;
	{
		//根据输入流创建输出流（Create output AVStream according to input AVStream）
		AVStream* in_stream = ifmt_ctx->streams[i];
		AVCodecParameters* in_codecpar = in_stream->codecpar;
		AVStream* out_stream = NULL;
		if (in_codecpar->codec_type != AVMEDIA_TYPE_AUDIO &&
			in_codecpar->codec_type != AVMEDIA_TYPE_VIDEO)
		{
			//这里将丢弃的流值存为-1,方便后续读帧时丢弃。
			stream_mapping[i] = -1;
			continue;
		}
		//将要保留的媒体流进行索引存储。
		stream_mapping[i] = stream_index;
		stream_index++;
		//新建一个媒体流
		out_stream = avformat_new_stream(ofmt_ctx, NULL);
		if (!out_stream)
		{
			std::cout << "avformat_new_stream failed" << std::endl;
			avformat_close_input(&ifmt_ctx);
			goto end;
		}
		//参数拷贝
		ret = avcodec_parameters_copy(out_stream->codecpar, in_codecpar);
		if (ret < 0)
		{
			std::cout << "avcodec_parameters_copy filed!" << std::endl;
			goto end;
		}
		out_stream->codecpar->codec_tag = 0;
	}
	//输出一下格式------------------
	av_dump_format(ofmt_ctx, 0, out_filename, 1);
	//打开输出文件（Open output file）
	if (!(ofmt->flags & AVFMT_NOFILE)) {
		ret = avio_open(&ofmt_ctx->pb, out_filename, AVIO_FLAG_WRITE);
		if (ret < 0) {
			std::cout << "could not open the outputfile:" << out_filename << std::endl;
			goto end;
		}
	}
	//写文件头（Write file header）
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
		//获取pkt
		ret = av_read_frame(ifmt_ctx, pkt);
		if (ret < 0)
		{
			std::cout << "=== read the end of the file！" << std::endl;
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
		//时间基数转换
		//转换PTS/DTS（Convert PTS/DTS）
		pkt->pts = av_rescale_q_rnd(pkt->pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt->dts = av_rescale_q_rnd(pkt->dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt->duration = av_rescale_q(pkt->duration, in_stream->time_base, out_stream->time_base);
		//std::cout << pkt->pts << "=" << pkt->dts << "=" << pkt->duration << std::endl;
		//std::cout << pkt->stream_index << "=" << pkt->flags << "=" << pkt->size<< std::endl;
		pkt->pos = -1;
		*/

		//写入（Write）
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
		//记得引用计数减1,否则会引起内存泄漏。
		av_packet_unref(pkt);
	}
	//写文件尾（Write file trailer）

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