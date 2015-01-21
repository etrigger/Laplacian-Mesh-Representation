void SaveMatrixXd(MatrixXd &src, QString filepath)
{
    std::ofstream file(filepath.toStdString().c_str());
    if(file.is_open()){
        file<<"Matrix :\n"<<src<<"\n";
        file.close();return;
    }
    std::cerr<<"file cannot be opened";
}

void SaveVectorXd(VectorXd &src , QString filepath)
{
    std::ofstream file(filepath.toStdString().c_str());
    if(file.is_open()){
        file<<"Vector :\n"<<src<<"\n";
        file.close();return;
    }
    std::cerr<<"file cannot be opened";
}