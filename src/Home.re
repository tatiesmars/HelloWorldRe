open BsReactNative;

let adUntId = "ca-app-pub-1425926517331745~6816357585";
let bannerId = "ca-app-pub-6500075216701705/2667297034";

type item = {
  key: string,
  text: string,
  order: int,
  finish: bool
};

type state = {
  tasks: list(item),
  toggle: bool
};

type action =
  | UpserTask(item)
  | DeleteTask(item)
  | ElseToggle(bool);


let () = BsExpo.Constants.constants##manifest |> Js.log |> ignore; 
let () = BsExpo.AdMob.make |> Js.log |> ignore; 
let windowWidth = Dimensions.(get(`window))##width;

let onButtonPress = v => Alert.alert(~title={j|你好，$v|j}, ());

let component = ReasonReact.reducerComponent("Home");

let renderItem = (onPress, onDelete, onEdit) =>
  FlatList.renderItem(({item}) =>
    <View
      style=Style.(
              style([
                flex(1.),
                borderBottomWidth(0.5),
                borderColor("#222"),
                width(Pt(float_of_int(windowWidth)))
              ])
            )>
      <TodoCell
        value=item.text
        toggle=item.finish
        onToggle=(b => onPress({...item, finish: b}))
        onDelete=(() => onDelete(item))
        onEdit=(s => onEdit({...item, text: s}))
      />
    </View>
  );

/* <View style=Style.(style([flex(0.1), backgroundColor("#444")]))>
       <View> <Text> (ReasonReact.stringToElement("Header")) </Text> </View>
     </View>
     <View style=Style.(style([flex(0.8)]))> <Home name="Home" /> </View>
     <View style=Style.(style([flex(0.1), backgroundColor("#444")]))>
       <View> <Text> (ReasonReact.stringToElement("Footer")) </Text> </View>
     </View>
   </View> */
let make = (~title: string, _children) => {
  ...component,
  initialState: () => {tasks: [], toggle: false},
  reducer: (action, state) =>
    switch action {
    | ElseToggle(b) => ReasonReact.Update({toggle: b, tasks: []})
    | DeleteTask(i) =>
      ReasonReact.Update({
        ...state,
        tasks: List.filter(x => x.key !== i.key, state.tasks)
      })
    | UpserTask(i) =>
      ReasonReact.Update({
        ...state,
        tasks: [i, ...List.filter(x => x.key !== i.key, state.tasks)]
      })
    },
  render: self =>
    <View
      style=Style.(
              style([
                flex(1.),
                justifyContent(Center),
                alignItems(Center),
                backgroundColor("#444"),
                width(Pt(float_of_int(windowWidth)))
              ])
            )>
      <StatusBar barStyle=`lightContent hidden=false />
      <View
        style=Style.(style([flex(0.13),flexDirection(ColumnReverse), width(Pt(float_of_int(windowWidth)))]))>
        <View style=Style.(style([flexDirection(Row), justifyContent(SpaceBetween)]))>
          <Text> (ReasonReact.stringToElement(title)) </Text>
          <Button
            title="Add +"
            color="#f08080"
            onPress=(
              _e =>
                self.send(
                  UpserTask({
                    key: string_of_int(Random.int(100000)),
                    order: List.length(self.state.tasks),
                    text: "My task",
                    finish: false
                  })
                )
            )
          />
        </View>
      </View>
      <View
        style=Style.(
                style([
                  flex(0.78),
                  flexDirection(Column),
                  justifyContent(Center),
                  alignItems(Center),
                  backgroundColor("#EEE"),
                  width(Pt(float_of_int(windowWidth)))
                ])
              )>
        <FlatList
          renderItem=(
            renderItem(
              item => self.send(UpserTask(item)),
              item => self.send(DeleteTask(item)),
              item => self.send(UpserTask(item))
            )
          )
          keyExtractor=((item, _) => item.key)
          data=(
            Array.of_list(
              List.sort((x, y) => x.order - y.order, self.state.tasks)
            )
          )
        />
      </View>
      <View
        style=Style.(style([flex(0.09), width(Pt(float_of_int(windowWidth)))]))>
        <View>
          <Text> (ReasonReact.stringToElement("eqd")) </Text>
        </View>
      </View>
    </View>
};