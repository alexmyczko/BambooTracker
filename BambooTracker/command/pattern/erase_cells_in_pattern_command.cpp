#include "erase_cells_in_pattern_command.hpp"

EraseCellsInPatternCommand::EraseCellsInPatternCommand(std::weak_ptr<Module> mod,
													   int songNum, int beginTrack, int beginColmn,
													   int beginOrder, int beginStep,
													   int endTrack, int endColumn, int endStep)
	: mod_(mod),
	  song_(songNum),
	  bTrack_(beginTrack),
	  bCol_(beginColmn),
	  order_(beginOrder),
	  bStep_(beginStep),
	  eTrack_(endTrack),
	  eCol_(endColumn),
	  eStep_(endStep)
{
	auto& sng = mod.lock()->getSong(songNum);
	int s = beginStep;

	int h = endStep - beginStep + 1;
	int w = 0;
	int tr = endTrack;
	int cl = endColumn;
	while (true) {
		if (tr == beginTrack) {
			w += (cl - beginColmn + 1);
			break;
		}
		else {
			w += (cl + 1);
			cl = 10;
			--tr;
		}
	}

	for (size_t i = 0; i < h; ++i) {
		prevCells_.emplace_back();
		int t = beginTrack;
		int c = beginColmn;
		for (size_t j = 0; j < w; ++j) {
			switch (c) {
			case 0:
				prevCells_.at(i).push_back(std::to_string(
							sng.getTrack(t).getPatternFromOrderNumber(beginOrder).getStep(s).getNoteNumber()));
				break;
			case 1:
				prevCells_.at(i).push_back(std::to_string(
							sng.getTrack(t).getPatternFromOrderNumber(beginOrder).getStep(s).getInstrumentNumber()));
				break;
			case 2:
				prevCells_.at(i).push_back(std::to_string(
							sng.getTrack(t).getPatternFromOrderNumber(beginOrder).getStep(s).getVolume()));
				break;
			case 3:
				prevCells_.at(i).push_back(
							sng.getTrack(t).getPatternFromOrderNumber(beginOrder).getStep(s).getEffectID(0));
				break;
			case 4:
				prevCells_.at(i).push_back(std::to_string(
							sng.getTrack(t).getPatternFromOrderNumber(beginOrder).getStep(s).getEffectValue(0)));
				break;
			case 5:
				prevCells_.at(i).push_back(
							sng.getTrack(t).getPatternFromOrderNumber(beginOrder).getStep(s).getEffectID(1));
				break;
			case 6:
				prevCells_.at(i).push_back(std::to_string(
							sng.getTrack(t).getPatternFromOrderNumber(beginOrder).getStep(s).getEffectValue(1)));
				break;
			case 7:
				prevCells_.at(i).push_back(
							sng.getTrack(t).getPatternFromOrderNumber(beginOrder).getStep(s).getEffectID(2));
				break;
			case 8:
				prevCells_.at(i).push_back(std::to_string(
							sng.getTrack(t).getPatternFromOrderNumber(beginOrder).getStep(s).getEffectValue(2)));
				break;
			case 9:
				prevCells_.at(i).push_back(
							sng.getTrack(t).getPatternFromOrderNumber(beginOrder).getStep(s).getEffectID(3));
				break;
			case 10:
				prevCells_.at(i).push_back(std::to_string(
							sng.getTrack(t).getPatternFromOrderNumber(beginOrder).getStep(s).getEffectValue(3)));
				break;
			}

			++c;
			t += (c / 11);
			c %= 11;
		}
		++s;
	}
}

void EraseCellsInPatternCommand::redo()
{
	auto& sng = mod_.lock()->getSong(song_);

	int s = bStep_;
	for (size_t i = 0; i < prevCells_.size(); ++i) {
		int t = bTrack_;
		int c = bCol_;
		for (size_t j = 0; j < prevCells_.at(i).size(); ++j) {
			switch (c) {
			case 0:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s).setNoteNumber(-1);
				break;
			case 1:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s).setInstrumentNumber(-1);
				break;
			case 2:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s).setVolume(-1);
				break;
			case 3:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s).setEffectID(0, "--");
				break;
			case 4:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s).setEffectValue(0, -1);
				break;
			case 5:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s).setEffectID(1, "--");
				break;
			case 6:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s).setEffectValue(1, -1);
				break;
			case 7:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s).setEffectID(2, "--");
				break;
			case 8:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s).setEffectValue(2, -1);
				break;
			case 9:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s).setEffectID(3, "--");
				break;
			case 10:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s).setEffectValue(3, -1);
				break;
			}

			++c;
			t += (c / 11);
			c %= 11;
		}

		++s;
	}
}

void EraseCellsInPatternCommand::undo()
{
	auto& sng = mod_.lock()->getSong(song_);

	int s = bStep_;
	for (size_t i = 0; i < prevCells_.size(); ++i) {
		int t = bTrack_;
		int c = bCol_;
		for (size_t j = 0; j < prevCells_.at(i).size(); ++j) {
			switch (c) {
			case 0:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s)
						.setNoteNumber(std::stoi(prevCells_.at(i).at(j)));
				break;
			case 1:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s)
						.setInstrumentNumber(std::stoi(prevCells_.at(i).at(j)));
				break;
			case 2:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s)
						.setVolume(std::stoi(prevCells_.at(i).at(j)));
				break;
			case 3:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s)
						.setEffectID(0, prevCells_.at(i).at(j));
				break;
			case 4:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s)
						.setEffectValue(0, std::stoi(prevCells_.at(i).at(j)));
				break;
			case 5:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s)
						.setEffectID(1, prevCells_.at(i).at(j));
				break;
			case 6:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s)
						.setEffectValue(1, std::stoi(prevCells_.at(i).at(j)));
				break;
			case 7:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s)
						.setEffectID(2, prevCells_.at(i).at(j));
				break;
			case 8:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s)
						.setEffectValue(2, std::stoi(prevCells_.at(i).at(j)));
				break;
			case 9:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s)
						.setEffectID(3, prevCells_.at(i).at(j));
				break;
			case 10:
				sng.getTrack(t).getPatternFromOrderNumber(order_).getStep(s)
						.setEffectValue(3, std::stoi(prevCells_.at(i).at(j)));
				break;
			}

			++c;
			t += (c / 11);
			c %= 11;
		}

		++s;
	}
}

int EraseCellsInPatternCommand::getID() const
{
	return 0x2e;
}
