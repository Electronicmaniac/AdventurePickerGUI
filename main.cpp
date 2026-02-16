#include <gtkmm.h>
#include <iostream>
#include <string>
#include <vector>

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

        set_child(m_main_box);

        // Start with the first question
        show_question("Ga je mee op een avontuur?",
                     {"Ja, ik ga graag op avontuur", "Nee"});
    }

protected:
    Gtk::Box m_main_box;
    Gtk::Label m_question_label;
    Gtk::Box m_button_box;

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
    
    void show_outcome(const std::string& text) {
        m_question_label.set_markup("<span size='xx-large'>Bestemming: " + text + "</span>");

        // Clear previous buttons
        while (auto child = m_button_box.get_first_child()) {
            m_button_box.remove(*child);
        }

        auto restart_button = Gtk::make_managed<Gtk::Button>("Opnieuw beginnen");
        restart_button->set_margin(10);
        restart_button->signal_clicked().connect([this]() {
            show_question("Ga je mee op een avontuur?",
                         {"Ja, ik ga graag op avontuur", "Nee"});
        });
        m_button_box.append(*restart_button);

        auto exit_button = Gtk::make_managed<Gtk::Button>("Afsluiten");
        exit_button->set_margin(10);
        exit_button->signal_clicked().connect([this]() {
            set_visible(false);
        });
        m_button_box.append(*exit_button);
    }

    void on_answer_clicked(const std::string& answer) {
        if (answer == "Ja, ik ga graag op avontuur") {
            show_question("Heb je zeebenen of reis je liever over het vaste land?", {"Vaste land", "Ik heb zeebenen"});
        } else if (answer == "Vaste land") {
            show_question("Sprechen zie ein biete deutch?", {"Aber naturlich", "Nein man"});
        } else if (answer == "Aber naturlich") {
            show_outcome("Duitsland");
        } else if (answer == "Nein man") {
            show_outcome("Wallonië");
        } else if (answer == "Ik heb zeebenen") {
            show_question("The torch reveals a hidden path! Follow it?", {"Follow", "Stay put"});
        } else if (answer == "Follow") {
            show_outcome("The Caribbean");
        } else if (answer == "Stay put") {
            show_outcome("The Harbor");
        } else if (answer == "Nee") {
            set_visible(false);
        } else {
            show_question("The adventure continues...", {"Restart"});
        }

        if (answer == "Restart") {
            show_question("Ga je mee op een avontuur?",
                         {"Ja, ik ga graag op avontuur", "Nee"});
        }
    }
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.example.adventure");
    return app->make_window_and_run<AdventureWindow>(argc, argv);
}
