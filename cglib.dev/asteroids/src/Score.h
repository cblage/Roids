#pragma once
#ifndef SCORE_H
#define SCORE_H
#pragma message("Score is included")


namespace asteroids {

	class Score
	{
	private:
		double _score;
	public:
		Score();
		Score(double score);
		~Score();
		void update(double score);
		void setScore(double score);
		double getScore(void);
	};
}

#endif