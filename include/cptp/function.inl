//#include "function.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace cptp{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    cptp Space    )//
    //-> function.hpp function.hpp
    inline double pointToCenti (double pt_) noexcept
    {
        return pt_*0.03528;
    }


    inline double centiToPoint (double centi_) noexcept
    {
        return centi_*28.3;
    }


    inline uint32_t scaleInterval(uint32_t iw_) noexcept{
        
        uint32_t ot;
        switch(iw_){
            case  3: ot=1;   break;
            case  4: ot=1;   break;
            case  5: ot=1;   break;
            case  6: ot=1;   break;
            case  7: ot=1;   break;
            case  8: ot=2;   break;
            case  9: ot=3;   break;
            case 10: ot=2;   break;
            case 11: ot=1;   break;
            case 12: ot=3;   break;
            case 13: ot=1;   break;
            case 14: ot=2;   break;
            case 15: ot=3;   break;
            case 16: ot=4;   break;
            case 17: ot=2;   break;
            case 18: ot=6;   break;
            case 19: ot=2;   break;
            case 20: ot=5;   break;
            case 21: ot=3;   break;
            case 22: ot=2;   break;
            case 23: ot=3;   break;
            case 24: ot=4;   break;
            case 25: ot=5;   break;
            case 26: ot=2;   break;
            case 27: ot=3;   break;
            case 28: ot=4;   break;
            case 29: ot=4;   break;
            case 30: ot=5;   break;
            default: ot=1;   break;
        }

        return ot;
    }


    inline size_t mathStrWidth(const std::string& str, size_t count) noexcept{
        size_t ot=count;
        size_t cominit=str.find_first_of("\\_^"); //Searching Command Charcters
        std::string befcomstr, aftcomstr;

        if(cominit==std::string::npos){
            //Math String without Command
            //Remove '{' and '}' for the decision of math string width
            std::string editstr=str;
            for(size_t braket=editstr.find_first_of("{}"); braket!=std::string::npos; braket=editstr.find_first_of("{}")){
                editstr.erase(str.begin()+braket);
            }

            return ot+=editstr.length()*2;

        }else{
        //Math String with Command
            befcomstr=str.substr(0, cominit);
            aftcomstr=str.substr(cominit+1);
            ot+=mathStrWidth(befcomstr);
        }

        if(str[cominit]=='\\'){
            //Math String including Back Slash Command
            //For Frac Command
            if(str.length()>cominit+5){
                std::string fracstr=str.substr(cominit+1, 5);
                if(fracstr=="frac{"){
                    std::string numdenstr=str.substr(cominit+6);
                    //Getting numerator characters
                    size_t braket=0;    //Position of braket, { and }
                    for(int numbra=1; numbra!=0; ++braket){
                        if(braket>numdenstr.length()){
                            std::cerr<<"Error: The numbers of left and right braket do not match"<<std::endl;
                            std::exit(EXIT_FAILURE);
                        }

                        braket=numdenstr.find_first_of("{}", braket);
                    
                        if(braket==std::string::npos){
                            std::cerr<<"Error: Something wrong in key name(numerator)"<<std::endl;
                            std::exit(EXIT_FAILURE);
                        }
                        else if (numdenstr[braket]=='{' && numdenstr[braket-1]!='\\') ++numbra;
                        else if (numdenstr[braket]=='}' && numdenstr[braket-1]!='\\') --numbra;
                    }

                    std::string numerstr=numdenstr.substr(0, braket-1);    //Numerator characters
                    std::string subseqstr=numdenstr.substr(braket+1);      //Subsequent characters
                    //Getting denominator charcters
                    braket=0;

                    for(int numbra=1; numbra!=0; ++braket){
                        if(braket>subseqstr.length()){
                            std::cerr<<"Error: The numbers of left and right braket do not match"<<std::endl;
                            std::exit(EXIT_FAILURE);
                        }

                        braket=subseqstr.find_first_of("{}", braket);
                    
                        if(braket==std::string::npos){
                            std::cerr<<"Error: Something wrong in key name(denominator)"<<std::endl;
                            std::exit(EXIT_FAILURE);
                        }
                        else if (subseqstr[braket]=='{' && subseqstr[braket-1]!='\\') ++numbra;
                        else if (subseqstr[braket]=='}' && subseqstr[braket-1]!='\\') --numbra;
                    }

                    std::string denomstr=subseqstr.substr(0, braket-1);

                    //Compearing between width of numer and denom 
                    size_t numerwd=mathStrWidth(numerstr);
                    size_t denomwd=mathStrWidth(denomstr);
                    size_t addwd;
                    if(numerwd>denomwd) addwd=numerwd;
                    else                addwd=denomwd;

                    //Send the left string to next
                    std::string sentstr=subseqstr.substr(braket);
                
                    return mathStrWidth(sentstr, ot+=addwd);
                }
            }


            //For other back slash commands
            size_t comfin=aftcomstr.find_first_of(" \\{");  //Check the last of command
            if(comfin==std::string::npos){
                //Independent command 
                return ot+=2;   //Add normal character size(2)
        
            }else if(aftcomstr[comfin]==' '){
                //Command terminal with space
                //send the left string to next
                std::string sentstr=aftcomstr.substr(comfin+1);
                return mathStrWidth(sentstr, ot+=2);
        
            }else if(aftcomstr[comfin]=='\\'){
                //Command terminal with next back slash
                //send the left string to next
                std::string sentstr=aftcomstr.substr(comfin);
            
            return mathStrWidth(sentstr, ot+=2);
        
            }else if(aftcomstr[comfin]=='{'){
                //Command with argument and braket
                //For exclusion of this braket  ->  \{ --something-- \}
                if(str[cominit+comfin]=='\\'){  //cominit+comfin is just before '{'
                    std::string sentstr=aftcomstr.substr(comfin+1);
                    return mathStrWidth(sentstr, ot+=4); //Send and add normal charsize*2(4)
                }

                //Getting content characters in braket
                std::string aftbrastr=aftcomstr.substr(comfin+1);
                size_t braket=0;
                for(int numbra=1; numbra!=0; ++braket){
                    if(braket>aftbrastr.length()){
                        std::cerr<<"Error: The numbers of left and right braket do not match"<<std::endl;
                        std::exit(EXIT_FAILURE);
                    }

                    braket=aftbrastr.find_first_of("{}", braket);
                
                    if(braket==std::string::npos){
                        std::cerr<<"Error: Something wrong in key name(\\comand{})"<<std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                    else if(aftbrastr[braket]=='{' && aftbrastr[braket-1]!='\\') ++numbra;
                    else if(aftbrastr[braket]=='}' && aftbrastr[braket-1]!='\\') --numbra;
                }

                std::string bracontstr=aftbrastr.substr(0, braket-1);

                //send the left string to next after getting width of contents in braket
                std::string sentstr=aftbrastr.substr(braket);
                return mathStrWidth(sentstr, ot+=mathStrWidth(bracontstr));

            }else{
                std::cerr<<"Error: Something wrong in key name(others)"<<std::endl;
                std::exit(EXIT_FAILURE);
            }
        }else if(str[cominit]=='_'){
            //Math string including under bar
            if(str[cominit+1]=='{'){
            //Under bar comamnd with braket 
            //Getting content characters in braket
                std::string aftbrastr=aftcomstr.substr(1);
                size_t braket=0;
                for(int numbra=1; numbra!=0; ++braket){

                    if(braket>aftbrastr.length()){
                        std::cerr<<"Error: The numbers of left and right braket do not match"<<std::endl;
                        std::exit(EXIT_FAILURE);
                    }

                    braket=aftbrastr.find_first_of("{}", braket);
                
                    if(braket==std::string::npos){
                        std::cerr<<"Error: Something wrong in key name(_{})"<<std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                    else if(aftbrastr[braket]=='{' && aftbrastr[braket-1]!='\\') ++numbra;
                    else if(aftbrastr[braket]=='}' && aftbrastr[braket-1]!='\\') --numbra;
                }

                std::string bracontstr=aftbrastr.substr(0, braket-1);

                //send the left string to next after getting width of contents in braket
                std::string sentstr=aftbrastr.substr(braket);
                return mathStrWidth(sentstr, ot+=mathStrWidth(bracontstr));
        
            }else{
                //Under bar comamnd without braket
                std::string sentstr=str.substr(cominit+2);
                return mathStrWidth(sentstr, ot+=1);
        
            }

        }else if(str[cominit]=='^'){
            //Math string including hat
            if(str[cominit+1]=='{'){
                //Hat comamnd with braket 
                //Getting content characters in braket
                std::string aftbrastr=aftcomstr.substr(1);
                size_t braket=0;

                for(int numbra=1; numbra!=0; ++braket){

                    if(braket>aftbrastr.length()){
                        std::cerr<<"Error: The numbers of left and right braket do not match"<<std::endl;
                        std::exit(EXIT_FAILURE);
                    }

                    braket=aftbrastr.find_first_of("{}", braket);
                
                    if(braket==std::string::npos){
                        std::cerr<<"Error: Something wrong in key name(^{})"<<std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                    else if(aftbrastr[braket]=='{' && aftbrastr[braket-1]!='\\') ++numbra;
                    else if(aftbrastr[braket]=='}' && aftbrastr[braket-1]!='\\') --numbra;
                }

                std::string bracontstr=aftbrastr.substr(0, braket-1);

                //send the left string to next after getting width of contents in braket
                std::string sentstr=aftbrastr.substr(braket);
                return mathStrWidth(sentstr, ot+=mathStrWidth(bracontstr));
        
            }else{
                //hat comamnd without braket
                std::string sentstr=str.substr(cominit+2);
                return mathStrWidth(sentstr, ot+=1);
            
            }
        }
        std::exit(EXIT_FAILURE);
    }
    

    inline size_t keyWidth(const std::string& key) noexcept
    {
        struct Math{
            size_t init;
            size_t fin;
        };
        gd::List<Math> mathstrs;
        
        for(unsigned int a=0; a<key.length(); ++a){
            size_t mathinit=key.length();
            size_t mathfin=key.length();
            if(key[a]=='$' && (a==0 || key[a-1]!='\\')){
                mathinit=a;
                unsigned int b;
                for(b=a+1; b<key.length(); ++b){
                    if(key[b]=='$' && key[mathinit-1]!='\\'){
                        mathfin=b;
                        mathstrs.pushBack({mathinit, mathfin});
                        a=b;
                        break;
                    }
                }
            
                if(b>key.length()){
                    std::cerr<<"Warning: '$' is maybe insufficient in key name"<<std::endl;
                }
            }
        }
        size_t mathwidth=0;
        size_t mathchars=0;
        for(uint a=0; a<mathstrs.size(); ++a){
            Math& math=mathstrs[a];
            mathwidth+=mathStrWidth(key.substr(math.init+1, math.fin-(math.init+1)));
            mathchars+=math.fin-math.init+1;
        }

        return key.length()-mathchars+(mathwidth+1)/2;
    }
}
