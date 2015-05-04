/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ChuckPluginTest4AudioProcessorEditor::ChuckPluginTest4AudioProcessorEditor (ChuckPluginTest4AudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    LookAndFeel::setDefaultLookAndFeel(new LookAndFeel_V3());
    // This is where our plugin's editor size is set.
    setSize (600, 700);
    addAndMakeVisible(addShredButton=new TextButton("Add Shred"));
    addShredButton->setButtonText("Add Shred");
    addShredButton->setBounds(0, 0, 100,100 );
    addShredButton->addListener(this);
    
    addAndMakeVisible(removeShredButton=new TextButton("Remove Shred"));
    removeShredButton->setButtonText("Remove Shred");
    removeShredButton->setBounds(120, 0, 100,100 );
    removeShredButton->addListener(this);
    
    //addAndMakeVisible(browseCodeButton=new TextButton("Browse Code"));
    //browseCodeButton->setButtonText("Browse Code");
    //browseCodeButton->setBounds(120, 120, 100,100 );
    //browseCodeButton->addListener(this);
    
    addAndMakeVisible(addFileContainerButton=new TextButton("Add file container"));
    addFileContainerButton->setButtonText("Add file container");
    addFileContainerButton->setBounds(220, 0, 100,100 );
    addFileContainerButton->addListener(this);
    
    
    
    addAndMakeVisible(getProcessor()->codeEditorDemo);
    getProcessor()->codeEditorDemo->setBounds(0, 130, getWidth(),getHeight()-130);
    
    //addAndMakeVisible(managerUI=new FileContainerManagerUI(getProcessor()->fileContainerManagerModel));
    //getProcessor()->codeEditorDemo->setBounds(0, 130, getWidth(),getHeight()-130);
    
    
    //lastFileLoaded=getProcessor()->fileManager.fileName;
    
    startTimer(50);
    timerCallback();
    

    
}

ChuckPluginTest4AudioProcessorEditor::~ChuckPluginTest4AudioProcessorEditor()
{
}

//==============================================================================
void ChuckPluginTest4AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    g.setColour (Colours::black);
    g.setFont (15.0f);
    //g.drawFittedText ("File Loaded: " + lastFileLoaded,
      //                0, 0, getWidth(), getHeight(),
        //              Justification::topRight, 1);
}

void ChuckPluginTest4AudioProcessorEditor::buttonClicked(Button *buttonThatWasPressed)
{
    if (buttonThatWasPressed==addShredButton)
    {
        getProcessor()->addShred();
    }
    
    if (buttonThatWasPressed==removeShredButton)
    {
        getProcessor()->removeShred();
    }
    
    if (buttonThatWasPressed==addFileContainerButton)
    {
        getProcessor()->fileContainerManagerModel->addFileContainer();
    }
        
    
    
    //if (buttonThatWasPressed==browseCodeButton) {
    //    getProcessor()->fileManager.openBrowser();
    //    lastFileLoaded=getProcessor()->fileManager.fileName;
    //}
}

void ChuckPluginTest4AudioProcessorEditor::timerCallback()
{
    
}

void ChuckPluginTest4AudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    
}
