#include "24GameAlgo.h"

int main(){
    srand(time(0));
    createQuestions(); 
    int count = 0;
    while (true){
        count++;
        int type_games = rand()%90+10;
        string goalstr = to_string(type_games);
        double goal = (double)type_games;
        newCreateList(type_games);
        string setNumber = newGetfile();
        clearSolvector();
        double setNumberDoubleType[4];
        int goal_int = stoi(goalstr);
        for (int i = 0;i<setNumber.size();i++){setNumberDoubleType[i] = (double)(setNumber[i]-48);}
        Solvethegame(setNumberDoubleType,goal_int);
        if (solutions.size() == 1){
            cout << "Game Gen : " << goalstr << " !=" << "   Can only Be solve : " << solutions[0] <<"   =>    " << setNumber << endl;
            return 0;
        }
        if (goalstr != solutions[0]){
            cout << "Game Gen : " << goalstr << " !=" << "   Can only Be solve : " << solutions[0] <<"   =>    " << setNumber << endl;
            return 0;
        }
        cout << endl;
        cout << count << ". " << setNumber << " = " << goal << endl;
        for(auto const & s : solutions) {
            cout << s << endl;
        }
        cout << endl;
        cout << " ------------------------------ " << endl;
    }
}
