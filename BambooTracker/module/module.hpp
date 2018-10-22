#pragma once

#include <vector>
#include <string>
#include "song.hpp"
#include "groove.hpp"

class Module
{
public:
	Module(std::string filePath = "", std::string title = u8"", std::string author = u8"",
		   std::string copyright = u8"", std::string comment = u8"", unsigned int tickFreq = 60);

	void setFilePath(std::string path);
	std::string getFilePath() const;
	void setTitle(std::string title);
	std::string getTitle() const;
	void setAuthor(std::string author);
	std::string getAuthor() const;
	void setCopyright(std::string copyright);
	std::string getCopyright() const;
	void setComment(std::string comment);
	std::string getComment() const;
	void setTickFrequency(unsigned int freq);
	unsigned int getTickFrequency() const;
	void setStepHighlightDistance(size_t dist);
	size_t getStepHighlightDistance() const;
	size_t getSongCount() const;
	size_t getGrooveCount() const;

	void addSong(SongType songType, std::string title);
	void sortSongs(std::vector<int> numbers);
	Song& getSong(int num);

	void addGroove();
	void removeGroove(int num);
	void setGroove(int num, std::vector<int> seq);
	void setGrooves(std::vector<std::vector<int>> seqs);
	Groove& getGroove(int num);

private:
	std::string filePath_;
	std::string title_;
	std::string author_;
	std::string copyright_;
	std::string comment_;
	unsigned int tickFreq_;
	size_t stepHlDist_;
	std::vector<Song> songs_;
	std::vector<Groove> grooves_;
};
