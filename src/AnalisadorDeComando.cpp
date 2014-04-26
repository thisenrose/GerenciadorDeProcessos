#include "include/AnalisadorDeComando.h"

AnalisadorDeComando::AnalisadorDeComando() {

}

vector<string> AnalisadorDeComando::separarParametros(string comando) {
	vector<string> tokens;
	std::string delimiter = " ";
	size_t pos = 0;
	std::string token;
	while ((pos = comando.find(delimiter)) != std::string::npos) {
		token = comando.substr(0, pos);
		tokens.push_back(token);
		comando.erase(0, pos + delimiter.length());
	}
	tokens.push_back(comando);
	return tokens;
}

bool AnalisadorDeComando::validarComando(string comando) {
	vector<string> partesDoComando = separarParametros(comando);

	for (string & c : getComandosDisponiveis()) {
		if (c == partesDoComando[0]) {
			if (partesDoComando[0] == "add") {
				// add nome grandeza tempoEmQueEntraNoSistema tempoNecessarioDeExecucao prioridade = 6
				if (partesDoComando.size() == 6) {
					// testa a grandeza (s ou ms)
					if (partesDoComando[2] == "s"
							|| partesDoComando[2] == "ms") {
						// testa se os tempos e a prioridade são números
						if (isNumero(partesDoComando[3])
								&& isNumero(partesDoComando[4])
								&& isNumero(partesDoComando[5])) {
							int prioridade = atoi(partesDoComando[5].c_str());
							// testa se está no intervalo permitido [1-10]
							if (prioridade >= PRIORIDADE_MINIMA
									&& prioridade <= PRIORIDADE_MAXIMA) {
								return true;
							}
						}
					}
				}
				return true;
			} else if(partesDoComando.size() == 1){
				return true;
			}
		}
	}
	return false;
}

vector<string> AnalisadorDeComando::getComandosDisponiveis() {
	return comandosDisponiveis;
}

bool AnalisadorDeComando::isNumero(const std::string& s) {
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it))
		++it;
	return !s.empty() && it == s.end();
}
