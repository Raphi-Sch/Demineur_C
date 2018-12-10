#ifndef _save_
#define _save_


//Lecture-Ecriture fichier
void save_file(const liste_t score);
liste_t load_file();


//Action sur la liste des scores
int position(liste_t scores, int best);
void save(liste_t scores, int best, int pos_save);

//Première liste de scores
liste_t premiers_scores(liste_t scores);

#endif
