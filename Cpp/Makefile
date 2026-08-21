# Compile chaque chapitre en un exécutable séparé dans build/
# Utilisation :
#   make               -> compile tous les chapitres
#   make classes_objets -> compile uniquement 02_classes_objets.cpp (par exemple)
#   make clean         -> supprime les exécutables générés
#   make run-templates -> compile ET exécute 05_templates.cpp

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
SRC_DIR = src
BUILD_DIR = build

CHAPITRES = 01_bases_cpp 02_classes_objets 03_heritage_polymorphisme 04_memoire_moderne 05_templates 06_stl_conteneurs 07_exceptions 08_operateurs_surcharge

.PHONY: all clean $(CHAPITRES) $(addprefix run-,$(CHAPITRES))

all: $(BUILD_DIR) $(CHAPITRES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(CHAPITRES): % : $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $(BUILD_DIR)/$@

run-%: %
	./$(BUILD_DIR)/$*

clean:
	rm -rf $(BUILD_DIR)
