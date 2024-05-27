#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;
mutex mtx;

void encontrarDoisMaiores(const vector<int> &numeros, int &maior1, int &maior2){
    maior1 = maior2 = numeric_limits<int>::min();
    for (int i = 0; i < numeros.size(); ++i){
        if (numeros[i] > maior1){
            lock_guard<mutex> lock(mtx);
            
            if (numeros[i] > maior1){
                maior2 = maior1;
                maior1 = numeros[i];
            }
        }
        else if (numeros[i] > maior2){
            lock_guard<mutex> lock(mtx);
            
            if (numeros[i] > maior2)
                maior2 = numeros[i];
        }
    }
}
int main()
{
    int n;
    
    cout << "Digite a quantidade de números: ";
    cin >> n;
    
    vector<int> numeros(n);
    
    cout << "Digite os números:\n";
    
    for (int i = 0; i < n; ++i)
        cin >> numeros[i];
    
    int maior1, maior2;
    
    thread t(encontrarDoisMaiores, ref(numeros), ref(maior1), ref(maior2));
    
    t.join();
    
    cout << "Os dois maiores números são: " << maior1 << " e " << maior2 << endl;
    
    return 0;
}