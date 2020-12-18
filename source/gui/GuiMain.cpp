//
// Created by Ruurd Adema on 18/12/2020.
// Copyright (c) 2020 Owllab. All rights reserved.
//

#include <JuceHeader.h>

#include "../views/MainView.h"

class GuiMain : public juce::JUCEApplication
{
public:
    GuiMain() : mMainWindow(new MainWindow(getApplicationName())) {}

    const juce::String getApplicationName() override
    {
        return ProjectInfo::projectName;
    }

    const juce::String getApplicationVersion() override
    {
        return ProjectInfo::versionString;
    }

    bool moreThanOneInstanceAllowed() override
    {
        return true;
    }

    void initialise(const juce::String&) override {}

    void shutdown() override {}

    void systemRequestedQuit() override
    {
        quit();
    }

    class MainWindow : public juce::DocumentWindow
    {
    public:
        MainWindow(juce::String name) :
            DocumentWindow(
                name,
                juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
                    juce::ResizableWindow::backgroundColourId),
                DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar(true);
            setContentNonOwned(&mMainView, true);

            setResizable(true, true);
            centreWithSize(getWidth(), getHeight());

            setVisible(true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        MainView mMainView;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mMainWindow;
};

START_JUCE_APPLICATION(GuiMain)
