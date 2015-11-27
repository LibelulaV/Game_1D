#pragma warning(disable: 4996) 

#include <list>

#include "ranking.h"
#include "render.h"

#define RECORD_MIN_POINTS 100

struct TScore {
	int m_points; 
	char m_player_name[10]; 
};

static std::list<TScore *> ranking;
static std::list<TScore *>::const_iterator it_ranking;

bool rankingIsRecord(int score) {
	if (score >= RECORD_MIN_POINTS) 
		return true;
	else return false;
}

void rankingPrintScores() {
	int cont = 1; 
	for (it_ranking = ranking.begin(); it_ranking != ranking.end(); it_ranking++) {
		paintScore(cont, (*it_ranking)->m_player_name, (*it_ranking)->m_points);
		cont++; 
	}
}

void rankingPrintHighestNScores(int n) {
	if (n > ranking.size()) 
		rankingPrintScores(); 
	else {
		int cont = 1;
		it_ranking = ranking.begin();
		while (cont <= n) {
			paintScore(cont, (*it_ranking)->m_player_name, (*it_ranking)->m_points);
			cont++; 
		}
	}
}

void rankingRecordScore(int score) {
	bool exit = false; 
	TScore * new_score = new TScore();
	printf("\n\nPlease, introduce your name and press ENTER: "); 
	scanf("%s", new_score->m_player_name);
	new_score->m_points = score;

	if (ranking.empty()) 
		ranking.push_front(new_score); 
	else {
		TScore * first = ranking.front(); 
		TScore * last = ranking.back(); 
		if (first->m_points < score) 
			ranking.push_front(new_score);
		else if (last->m_player_name)
			ranking.push_back(new_score);
		else {
			it_ranking = ranking.begin();
			while (!exit || it_ranking != ranking.end()) {
				if ((*it_ranking)->m_points < score)
					ranking.insert(it_ranking, new_score);
				else it_ranking++;
			}
		}
	}
}

bool rankingIsEmpty() {
	return ranking.empty(); 
}

void rankingEnd() {
	it_ranking = ranking.begin(); 
	while (it_ranking != ranking.end()) {
		delete (*it_ranking);
		it_ranking = ranking.erase(it_ranking);
	}
	ranking.clear(); 
}
