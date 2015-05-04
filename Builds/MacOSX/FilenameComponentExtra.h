//
//  FilenameComponentExtra.h
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/25/15.
//
//

#ifndef __ChuckPluginTest4__FilenameComponentExtra__
#define __ChuckPluginTest4__FilenameComponentExtra__

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"


#endif /* defined(__ChuckPluginTest4__FilenameComponentExtra__) */


class FilenameComponentExtra  : public Component,
public SettableTooltipClient,
public FileDragAndDropTarget,
private AsyncUpdater,
private ButtonListener,  // (can't use Button::Listener due to idiotic VC2005 bug)
private ComboBoxListener
{
public:
    //==============================================================================
    /** Creates a FilenameComponent.
     
     @param name             the name for this component.
     @param currentFile      the file to initially show in the box
     @param canEditFilename  if true, the user can manually edit the filename; if false,
     they can only change it by browsing for a new file
     @param isDirectory      if true, the file will be treated as a directory, and
     an appropriate directory browser used
     @param isForSaving      if true, the file browser will allow non-existent files to
     be picked, as the file is assumed to be used for saving rather
     than loading
     @param fileBrowserWildcard  a wildcard pattern to use in the file browser - e.g. "*.txt;*.foo".
     If an empty string is passed in, then the pattern is assumed to be "*"
     @param enforcedSuffix   if this is non-empty, it is treated as a suffix that will be added
     to any filenames that are entered or chosen
     @param textWhenNothingSelected  the message to display in the box before any filename is entered. (This
     will only appear if the initial file isn't valid)
     */
    FilenameComponentExtra (const String& name,
                       const File& currentFile,
                       bool canEditFilename,
                       bool isDirectory,
                       bool isForSaving,
                       const String& fileBrowserWildcard,
                       const String& enforcedSuffix,
                       const String& textWhenNothingSelected);
    
    /** Destructor. */
    ~FilenameComponentExtra();
    
    //==============================================================================
    /** Returns the currently displayed filename. */
    File getCurrentFile() const;
    
    /** Returns the raw text that the user has entered. */
    String getCurrentFileText() const;
    
    /** Changes the current filename.
     
     @param newFile                the new filename to use
     @param addToRecentlyUsedList  if true, the filename will also be added to the
     drop-down list of recent files.
     @param notification           whether to send a notification of the change to listeners
     */
    void setCurrentFile (File newFile,
                         bool addToRecentlyUsedList,
                         NotificationType notification = sendNotificationAsync);
    
    /** Changes whether the use can type into the filename box.
     */
    void setFilenameIsEditable (bool shouldBeEditable);
    
    /** Sets a file or directory to be the default starting point for the browser to show.
     
     This is only used if the current file hasn't been set.
     */
    void setDefaultBrowseTarget (const File& newDefaultDirectory);
    
    /** This can be overridden to return a custom location that you want the dialog box
     to show when the browse button is pushed.
     The default implementation of this method will return either the current file
     (if one has been chosen) or the location that was set by setDefaultBrowseTarget().
     */
    virtual File getLocationToBrowse();
    
    /** Returns all the entries on the recent files list.
     
     This can be used in conjunction with setRecentlyUsedFilenames() for saving the
     state of this list.
     
     @see setRecentlyUsedFilenames
     */
    StringArray getRecentlyUsedFilenames() const;
    
    /** Sets all the entries on the recent files list.
     
     This can be used in conjunction with getRecentlyUsedFilenames() for saving the
     state of this list.
     
     @see getRecentlyUsedFilenames, addRecentlyUsedFile
     */
    void setRecentlyUsedFilenames (const StringArray& filenames);
    
    /** Adds an entry to the recently-used files dropdown list.
     
     If the file is already in the list, it will be moved to the top. A limit
     is also placed on the number of items that are kept in the list.
     
     @see getRecentlyUsedFilenames, setRecentlyUsedFilenames, setMaxNumberOfRecentFiles
     */
    void addRecentlyUsedFile (const File& file);
    
    /** Changes the limit for the number of files that will be stored in the recent-file list.
     */
    void setMaxNumberOfRecentFiles (int newMaximum);
    
    /** Changes the text shown on the 'browse' button.
     
     By default this button just says "..." but you can change it. The button itself
     can be changed using the look-and-feel classes, so it might not actually have any
     text on it.
     */
    void setBrowseButtonText (const String& browseButtonText);
    
    //==============================================================================
    /** Adds a listener that will be called when the selected file is changed. */
    void addListener (FilenameComponentListener* listener);
    
    /** Removes a previously-registered listener. */
    void removeListener (FilenameComponentListener* listener);
    
    /** Gives the component a tooltip. */
    void setTooltip (const String& newTooltip) override;
    
    //==============================================================================
    /** This abstract base class is implemented by LookAndFeel classes. */
    struct JUCE_API  LookAndFeelMethods
    {
        virtual ~LookAndFeelMethods() {}
        
        virtual Button* createFilenameComponentBrowseButton (const String& text) = 0;
        virtual void layoutFilenameComponent (FilenameComponent&, ComboBox* filenameBox, Button* browseButton) =  0;
    };
    
    //==============================================================================
    /** @internal */
    void paintOverChildren (Graphics&) override;
    /** @internal */
    void resized() override;
    /** @internal */
    void lookAndFeelChanged() override;
    /** @internal */
    bool isInterestedInFileDrag (const StringArray&) override;
    /** @internal */
    void filesDropped (const StringArray&, int, int) override;
    /** @internal */
    void fileDragEnter (const StringArray&, int, int) override;
    /** @internal */
    void fileDragExit (const StringArray&) override;
    /** @internal */
    KeyboardFocusTraverser* createFocusTraverser() override;
    
private:
    //==============================================================================
    ComboBox filenameBox;
    String lastFilename;
    ScopedPointer<Button> browseOpenButton;
    ScopedPointer<Button> browseSaveAsButton;
    
    int maxRecentFiles;
    bool isDir, isSaving, isFileDragOver;
    String wildcard, enforcedSuffix, browseButtonText;
    ListenerList <FilenameComponentListener> listeners;
    File defaultBrowseFile;
    
    void comboBoxChanged (ComboBox*) override;
    void buttonClicked (Button*) override;
    void handleAsyncUpdate() override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilenameComponentExtra)
};