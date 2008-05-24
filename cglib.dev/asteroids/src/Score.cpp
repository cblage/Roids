#include "Score.h"

namespace asteroids {

	Score::Score() {
		_score = 0;
	}

	Score::Score(double score) {
		_score = score;
	}
	
	Score::~Score() {
	}

	void Score::update(double points) {
		_score = _score + points;
	}

	void Score::setScore(double score) {
		_score = score;
	}

	double Score::getScore(void) {
		return _score;
	}
}
