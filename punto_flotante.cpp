#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;

int ObtSigno(bitset<32> numBin){
    return numBin[31];
}
int ObtExpo(bitset<32> numBin){
    bitset<8> Expo;
    for(int i = 23; i < 31; i++)
        Expo[i-23] = numBin[i];
    return Expo.to_ullong();
}
float ObtSigni(bitset<32> numBin){
    bitset<23> Significando;
    for(int i = 0; i < 23; i++)
        Significando[i] = numBin[i];
    float SigN_D = 1.0f;
    for(int i = 0; i < 23; i++){
        if(Significando[22-i]) SigN_D += pow(2, (-i-1)); //extraemos el valor decimal del significando 
    }
    return SigN_D;
}
float multiplicar(float num1, float num2){
    //si alguno es cero entonces retorna la multiplciacion cero
    if(int(num1) == 0 || int(num2) == 0){
        cout<<"| El resultado de la multiplicacion es 0"<<endl;
        return 0;
    }
    //determinar el signo del producto
    bitset<32> binA = bitset<32>(*reinterpret_cast<unsigned int*>(&num1));
    bitset<32> binB = bitset<32>(*reinterpret_cast<unsigned int*>(&num2));
    bool signo_res = ObtSigno(binA) ^ ObtSigno(binB);
    int expRealA = ObtExpo(binA)-127;
    int expRealB = ObtExpo(binB)-127;
    int sumaExp = expRealA + expRealB; //sumamos los exponentes reales 
    float SignA = ObtSigni(binA);
    float SignB = ObtSigni(binB);
    float prodSign = SignA * SignB;
    //verificar overflow o underflow en la suma
    if(sumaExp < -127 || sumaExp > 127){
        cout<<"Desbordamiento"<<endl;
        return 0;
    }
    //normalizar el significando
    while (prodSign >= 2.0f) {
        prodSign /= 2.0f;
        sumaExp++;
    }   
    while (prodSign < 1.0f) {
        prodSign *= 2.0f;
        sumaExp--;
    }

    float ResDec = prodSign * pow(2, sumaExp);
    if (signo_res) {
        ResDec *= -1.0f;
    }
    float multDirec = num1*num2;
    bitset<32> ResBin = bitset<32>(*reinterpret_cast<unsigned int*>(&ResDec));
    bitset<32> Resdirecto = bitset<32>(*reinterpret_cast<unsigned int*>(&multDirec)); 
    cout<<"| Resultado en decimal: "<<ResDec<<endl;
    cout<<"| Resultado en binario: "<<ResBin<<endl;
    cout<<"| Resultado directo:  "<<num1*num2<<endl;
    cout<<"| Resultado en binario directo: "<<Resdirecto<<endl;
}
int main(){
    float num1, num2;
    cout<<"\n\n=-=-=-= Multiplicacion en punto flotante =-=-=-="<<endl;
    cout<<"\t- Ingresa el primer numero: ";
    cin>>num1;
    cout<<"\t- Ingresa el segundo numero: ";
    cin>>num2;
    multiplicar(num1, num2);
}
