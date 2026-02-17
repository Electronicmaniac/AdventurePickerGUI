#include <gtkmm.h>
#include <iostream>
#include <string>
#include <vector>

namespace Adventures
{
    enum adventureType
    {
        MOESEL,
        TEXEL,
        GREVELINGENPARK,
        NATUURHUISJE
    };

    std::string ToString(adventureType eType)
    {
        switch (eType)
        {
        case MOESEL: return "Hotel aan de Moesel";
        case TEXEL: return "BnB Texel";
        case GREVELINGENPARK: return "Huisje Grevelingenstrand";
        case NATUURHUISJE: return "Natuurhuisje";
        default: return "Unknown";
        }
    }
}

class AdventureWindow : public Gtk::Window {
public:
    AdventureWindow() {
        set_title("Adventure Picker");
        fullscreen();

        // Setup the main layout container (vertical box)
        m_main_box.set_orientation(Gtk::Orientation::VERTICAL);
        m_main_box.set_spacing(20);
        m_main_box.set_margin(50);
        m_main_box.set_valign(Gtk::Align::CENTER);

        // Setup the question label
        m_question_label.set_halign(Gtk::Align::CENTER);
        m_main_box.append(m_question_label);

        // Setup the button box for answers
        m_button_box.set_spacing(10);
        m_button_box.set_halign(Gtk::Align::CENTER);
        m_main_box.append(m_button_box);

        // Setup the picture box for avatars
        picture_box.set_spacing(10);
        picture_box.set_halign(Gtk::Align::CENTER);
        m_main_box.append(picture_box);

        set_child(m_main_box);

        // Start with the first question
        show_question("Ga je mee op een avontuur?",
                     {"Ja, ik ga graag op avontuur", "Nee"});
    }

protected:
    Gtk::Box m_main_box;
    Gtk::Label m_question_label;
    Gtk::Box m_button_box;
    Gtk::Box picture_box;

    void show_question(const std::string& text, const std::vector<std::string>& options) {
        m_question_label.set_markup("<span size='xx-large'>" + text + "</span>");

        // Clear previous buttons
        while (auto child = m_button_box.get_first_child()) {
            m_button_box.remove(*child);
        }

        // Add new buttons for each option
        for (const auto& option : options) {
            auto button = Gtk::make_managed<Gtk::Button>(option);
            button->set_margin(10);
            button->signal_clicked().connect([this, option]() {
                on_answer_clicked(option);
            });
            m_button_box.append(*button);
        }
    }
    
    void show_outcome(const Adventures::adventureType adventure) {
        m_question_label.set_markup("<span size='xx-large'>Bestemming: " + Adventures::ToString(adventure) + "</span>");

        // Clear previous buttons
        while (auto child = m_button_box.get_first_child()) {
            m_button_box.remove(*child);
        }

        // Clear previous images
        while (auto child = picture_box.get_first_child()) {
            picture_box.remove(*child);
        }

        // Show picture
        auto lpicture = Gtk::make_managed<Gtk::Image>(Adventures::ToString(adventure) + ".png");
        lpicture->set_pixel_size(600);
        picture_box.append(*lpicture);
    }

    void on_answer_clicked(const std::string& answer) {
        if (answer == "Ja, ik ga graag op avontuur") {
            show_question("Heb je zeebenen of reis je liever over het vaste land?", {"Vaste land", "Ik heb zeebenen"});
        } else if (answer == "Vaste land") {
            show_question("Sprechen zie ein biete deutch?", {"Aber naturlich", "Nein man"});
        } else if (answer == "Aber naturlich") {
            show_outcome(Adventures::MOESEL);
        } else if (answer == "Nein man") {
            show_question("Huisje in een park of een losstaand huisje?", {"Park", "Losstaand huisje"});
        } else if (answer == "Park") {
            show_outcome(Adventures::GREVELINGENPARK);
        } else if (answer == "Losstaand huisje") {
            show_outcome(Adventures::NATUURHUISJE);
        } else if (answer == "Ik heb zeebenen") {
            show_question("Zin om een stukje te varen?", {"Ik wil wel varen", "Boten zijn niet mijn ding"});
        } else if (answer == "Ik wil wel varen") {
            show_outcome(Adventures::TEXEL);
        } else if (answer == "Boten zijn niet mijn ding") {
            show_outcome(Adventures::TEXEL);
        }

        if (answer == "Nee") {
            exit(0);
        }
    }
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.example.adventure");
    return app->make_window_and_run<AdventureWindow>(argc, argv);
}
