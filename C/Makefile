# Compile chaque chapitre en un exécutable séparé dans build/
# Utilisation :
#   make            -> compile tous les chapitres
#   make bases      -> compile uniquement 01_bases.c (par exemple)
#   make clean      -> supprime les exécutables générés
#   make run-bases  -> compile ET exécute 01_bases.c

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC_DIR = src
BUILD_DIR = build

CHAPITRES = 01_bases 02_pointeurs 03_tableaux_chaines 04_memoire_dynamique 05_structs_pointeurs_fonctions 06_fichiers_erreurs

.PHONY: all clean $(CHAPITRES) $(addprefix run-,$(CHAPITRES))

all: $(BUILD_DIR) $(CHAPITRES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(CHAPITRES): % : $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@

run-%: %
	./$(BUILD_DIR)/$*

clean:
	rm -rf $(BUILD_DIR) *.txt
